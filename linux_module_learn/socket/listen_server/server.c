#include <linux/kthread.h>
#include <linux/list.h>
#include <linux/net.h>
#include <linux/sched.h>
#include <net/sock.h>

static struct task_struct *server_thread;
static DECLARE_WAIT_QUEUE_HEAD(server_wq);

static DEFINE_MUTEX(server_mutex);
#define server_lock() mutex_lock(&server_mutex)
#define server_unlock() mutex_unlock(&server_mutex)
static LIST_HEAD(session_list);

enum sock_state {
	SERVER_OPEN = 1,
	SERVER_LISTEN,
	SERVER_RX,
	SERVER_TX,
	SERVER_CLOSED
};

struct server_session {
	struct list_head list;
	struct socket *sock;
	struct timer_list timer;
	unsigned long state;
	unsigned long flags;
	char buffer[1024];
	int recv_len;
};

static void server_schedule(void)
{
	wake_up_all(&server_wq);
}

static int server_sock_create(struct socket **sock)
{
	int err;

	err = sock_create_kern(&init_net, AF_INET, SOCK_STREAM, IPPROTO_TCP,
			       sock);
	return err;
}

static void server_session_timeout(struct timer_list *t)
{
	struct server_session *s = from_timer(s, t, timer);

	set_bit(ETIMEDOUT, &s->flags);
	pr_info("session %p state %ld", s, s->state);
	server_schedule();
}

static void server_session_set_timer(struct server_session *s, long timeout)
{
	pr_info("session %p state %ld timeout %ld", s, s->state, timeout);

	mod_timer(&s->timer, jiffies + timeout);
}

static struct server_session *server_session_add(struct socket *sock, int state)
{
	struct server_session *s = kzalloc(sizeof(*s), GFP_KERNEL);

	if (!s)
		return NULL;

	timer_setup(&s->timer, server_session_timeout, 0);

	s->state = state;
	s->sock = sock;

	list_add(&s->list, &session_list);
	// server_session_set_timer(s, 100 * HZ);
	pr_info("New session %p\n", s);

	return s;
}

static void session_change(struct sock *sk)
{
	pr_info("Session %p state change %d\n", sk, sk->sk_state);
	server_schedule();
}

static void session_ready(struct sock *sk)
{
	pr_info("Session %p ready\n", sk);
	server_schedule();
}

int server_add_listener(unsigned long int s_addr)
{
	struct sockaddr_in addr;
	struct socket *sock;
	struct server_session *s;
	int err = 0;

	/* Create socket */
	err = server_sock_create(&sock);
	if (err < 0) {
		return err;
	}

	/* Bind socket */
	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(s_addr);
	addr.sin_port = htons(6611);
	err = kernel_bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	if (err < 0) {
		goto failed;
	}

	/* Start listening on the socket */
	err = kernel_listen(sock, 10);
	if (err) {
		goto failed;
	}

	sock->sk->sk_data_ready = session_ready;
	sock->sk->sk_state_change = session_change;

	/* Add listening session */
	s = server_session_add(sock, SERVER_LISTEN);
	if (!s) {
		err = -ENOMEM;
		goto failed;
	}

	return 0;
failed:
	sock_release(sock);
	return err;
}

static void session_clear_timer(struct server_session *s)
{
	pr_info("session %p state %ld", s, s->state);
	del_timer_sync(&s->timer);
}

static struct server_session *server_session_del(struct server_session *s)
{
	list_del(&s->list);

	session_clear_timer(s);
	sock_release(s->sock);
	kfree(s);
	pr_info("Session %p deleted\n", s);

	return NULL;
}

static void server_kill_listener(void)
{
	struct server_session *s, *n;

	list_for_each_entry_safe(s, n, &session_list, list)
		server_session_del(s);
}

static void server_accept_connection(struct server_session *s)
{
	struct socket *sock = s->sock, *nsock;
	int err;

	err = kernel_accept(sock, &nsock, O_NONBLOCK);
	if (err < 0) {
		pr_info("Accept failed: %d\n", err);
		return;
	}
	pr_info("New connection %p\n", nsock);

	nsock->sk->sk_data_ready = session_ready;
	nsock->sk->sk_state_change = session_change;

	s = server_session_add(nsock, SERVER_OPEN);
	if (s) {
		server_schedule();
	} else {
		sock_release(nsock);
	}
}

static struct server_session *server_process_rx(struct server_session *s)
{
	struct socket *sock = s->sock;
	/*struct sock *sk = sock->sk;*/
	struct kvec iov;
	int len, buflen = sizeof(s->buffer);
	struct msghdr msg = {
		NULL,
	};

	iov.iov_base = s->buffer;
	iov.iov_len = (size_t)buflen;

	len = kernel_recvmsg(sock, &msg, &iov, 1, buflen, MSG_DONTWAIT);

	if (len < 0) {
		if (len != -EAGAIN) {
			s->state = SERVER_CLOSED;
			printk("receiving message error, len=%d\n", len);
		} else {
			// s->state = SERVER_RX;
			s->recv_len = 0;
		}
	} else {
		s->state = SERVER_RX;
		s->recv_len = len;
		printk("receiving: %s, len=%d\n", s->buffer, len);
	}

	/*if (s && (s->state == SERVER_CLOSED))*/
	/*	server_session_close(s, sk->sk_err);*/

	return s;
}

static struct server_session *server_process_tx(struct server_session *s)
{
	struct socket *sock = s->sock;
	/*struct sock *sk = sock->sk;*/
	struct kvec iov;
	int len = 0;
	struct msghdr msg = {
		NULL,
	};

	iov.iov_base = s->buffer;
	iov.iov_len = s->recv_len;
	pr_info("sending: %s, len=%d\n", s->buffer, s->recv_len);

	s->state = SERVER_TX;
	len = kernel_sendmsg(sock, &msg, &iov, 1, s->recv_len);

	if (len < 0)
		printk("sending message error, len=%d\n", len);
	else
		printk("sending: %s\n", s->buffer);

	/*if (s && (s->state == SERVER_CLOSED))*/
	/*	server_session_close(s, sk->sk_err);*/
	return s;
}

static void server_process_closed(struct server_session *s)
{
	pr_info("Session %p closed\n", s);
	s->state = SERVER_CLOSED;

	session_clear_timer(s);
	server_session_del(s);
}

static void server_process_sessions(void)
{
	struct server_session *s, *n;

	server_lock();

	list_for_each_entry_safe(s, n, &session_list, list) {
		pr_info("Processing session %p state %ld\n", s, s->state);
		if (test_and_clear_bit(ETIMEDOUT, &s->flags)) {
			s->state = ETIMEDOUT;
			server_session_del(s);
			continue;
		}
		switch (s->state) {
		case SERVER_LISTEN:
			server_accept_connection(s);
			continue;
		case SERVER_OPEN:
			server_process_rx(s);
		case SERVER_RX:
			server_process_tx(s);
		default:
			server_process_closed(s);
			break;
		}
	}

	server_unlock();
}

static int server_run(void *unused)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	set_user_nice(current, -10);

	server_add_listener(INADDR_ANY);

	add_wait_queue(&server_wq, &wait);
	while (!kthread_should_stop()) {
		server_process_sessions();
		wait_woken(&wait, TASK_INTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);
	}
	remove_wait_queue(&server_wq, &wait);

	server_kill_listener();

	return 0;
}

static int __init server_init(void)
{
	int err;

	server_thread = kthread_run(server_run, NULL, "kserverd");
	if (IS_ERR(server_thread)) {
		err = PTR_ERR(server_thread);
		goto unregister;
	}

	return 0;

unregister:
	return err;
}

static void __exit server_exit(void)
{
	kthread_stop(server_thread);
}

module_init(server_init);
module_exit(server_exit);
MODULE_LICENSE("GPL");
