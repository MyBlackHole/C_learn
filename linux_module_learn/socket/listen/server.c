#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <net/sock.h>

static struct task_struct *task; //内核线程任务头

//内核线程服务函数，重点！！！！
static int socket_threadfn(void *data)
{
	struct socket *sock, *nsock;
	struct sockaddr_in addr;
	int err;

	/* 使能信号处理接受 SIGINT 信号, 使内核线程可以唤醒
	 * 避免 kernel_accept 堵塞, 
	 * 导致无法执行 kthread_should_stop, 从而无法退出*/
	allow_signal(SIGINT);

	//建立套接字
	err = sock_create_kern(&init_net, PF_INET, SOCK_STREAM, IPPROTO_TCP,
			       &sock);
	if (err < 0) {
		printk("sock_create_kern failed.\n");
		return -1;
	}

	//绑定端口
	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(6611);
	err = kernel_bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	if (err < 0) {
		printk("kernel_bind failed.\n");
		sock_release(sock);
		return -1;
	}

	//监听端口
	err = kernel_listen(sock, 1024);
	if (err < 0) {
		printk("kernel_listen failed.\n");
		sock_release(sock);
		return -1;
	}

	//等待连接
	err = kernel_accept(sock, &nsock, 0);
	if (err < 0) {
		printk("kernel_accept failed.\n");
		sock_release(sock);
		return -1;
	}

	//任务主循环
	while (!kthread_should_stop()) {
		struct msghdr msg = {
			NULL,
		};
		struct kvec iov;
		char buffer[1024];
		int len, buflen = sizeof(buffer);

		iov.iov_base = buffer;
		iov.iov_len = (size_t)buflen;

		//等待sk_bufer中数据可读
		wait_event_interruptible(
			*sk_sleep(nsock->sk),
			!skb_queue_empty(&nsock->sk->sk_receive_queue) ||
				kthread_should_stop());

		if (!skb_queue_empty(&nsock->sk->sk_receive_queue)) {
			len = kernel_recvmsg(nsock, &msg, &iov, 1, buflen,
					     MSG_DONTWAIT);
			if (len < 0)
				printk("receiving message error\n");
			else
				printk("receiving: %s\n", buffer);
		}
	}
	sock_release(nsock);
	sock_release(sock);

	return 0;
}

int __init test_server_init(void)
{
	task = kthread_run(socket_threadfn, NULL, "listen thread");
	if (IS_ERR(task)) {
		printk("kthread_run failed.\n");
		return -1;
	}
	return 0;
}

void __exit test_server_exit(void)
{
	int ret = 0;

	/* 唤醒内核线程 */
	send_sig(SIGINT, task, 1);
	/* 会导致内核线程以退出情况下执行下面的代码
	 * 从而导致内核崩溃*/
	ssleep(10);
	/* 需要确保内核线程没有退出
	 * 不然会导致内核崩溃*/
	ret = kthread_stop(task);
	if (ret)
		printk("kthread_stop failed.\n");
}
module_init(test_server_init);
module_exit(test_server_exit);
MODULE_LICENSE("GPL");

// output
// insmod server.ko
//
// ./client
