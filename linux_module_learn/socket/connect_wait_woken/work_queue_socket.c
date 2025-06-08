#include "linux/slab.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/net.h>
#include <net/tcp.h>
#include <linux/inet.h>
#include <linux/in.h>
#include <linux/socket.h>
#include <linux/workqueue.h>

#define TARGET_IP "10.5.8.81" // 目标服务器IP
static char *target_ip = TARGET_IP;
module_param(target_ip, charp, 0644);
MODULE_PARM_DESC(target_ip, "Target IP address");
#define TARGET_PORT 8080 // 目标端口
static int target_port = TARGET_PORT;
module_param(target_port, int, 0644);
MODULE_PARM_DESC(target_port, "Target port number");

atomic_t done = ATOMIC_INIT(0); // 连接完成标志

// 定义工作结构体，包含 socket 和消息数据
struct socket_work {
	struct work_struct work;
	struct socket *sock;
	char *message;
};

static struct socket_work *s_work;

static void connect_state_change(struct sock *sk)
{
	switch (sk->sk_state) {
	case TCP_SYN_SENT:
		/* 连接进行中 */
		break;
	case TCP_ESTABLISHED:
		/* 连接成功 */
		atomic_set(&done, 1);
		pr_info("Connected successfully\n");
		wake_up_interruptible(sk_sleep(sk));
		break;
	default:
		/* 连接失败 */
		atomic_set(&done, -ECONNREFUSED);
		pr_err("Connect failed: %d\n", sk->sk_err);
		wake_up_interruptible(sk_sleep(sk));
	}
}

// 工作处理函数（异步执行连接和发送）
static void socket_worker(struct work_struct *work)
{
	int timeo = 10 * HZ; // 连接超时时间
	struct socket_work *s_work =
		container_of(work, struct socket_work, work);
	struct sockaddr_in sin;
	int ret;
	DEFINE_WAIT_FUNC(wait, woken_wake_function);

	// 1. 创建 TCP socket
	ret = sock_create_kern(&init_net, AF_INET, SOCK_STREAM, IPPROTO_TCP,
			       &s_work->sock);
	if (ret < 0) {
		pr_err("Failed to create socket: %d\n", ret);
		goto release_socket;
	}

	// 2. 设置目标地址
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(target_port);
	sin.sin_addr.s_addr = in_aton(target_ip);

	s_work->sock->sk->sk_state_change = connect_state_change;

	add_wait_queue(sk_sleep(s_work->sock->sk), &wait);
	// 3. 发起连接
	ret = s_work->sock->ops->connect(s_work->sock, (struct sockaddr *)&sin,
					 sizeof(sin), O_NONBLOCK);
	if (ret == -EINPROGRESS || ret == -EALREADY) {
		pr_warn("Connect in progress: %d\n", ret);
		/* 等待连接完成或超时 */
		timeo = wait_woken(&wait, TASK_INTERRUPTIBLE, timeo);
		if (!timeo) {
			ret = -ETIMEDOUT;
			pr_err("Connect timed out\n");
		}

		/* 检查最终状态 */
		switch (atomic_read(&done)) {
		case 1:
			ret = 0;
			break;
		case 0:
			ret = -ETIMEDOUT;
			break;
		default:
			ret = atomic_read(&done);
		}
	}
	if (ret < 0) {
		pr_err("Connect failed: %d\n", ret);
		goto release_wait;
	}

	pr_info("Connected to %s:%d\n", target_ip, target_port);

	s_work->sock->sk->sk_state_change = NULL;
	// 4. 发送数据
	{
		struct kvec vec = { .iov_base = s_work->message,
				    .iov_len = strlen(s_work->message) };
		struct msghdr msg_hdr = { .msg_flags = 0 };
		ret = kernel_sendmsg(s_work->sock, &msg_hdr, &vec, 1,
				     vec.iov_len);
		if (ret < 0) {
			pr_err("Send failed: %d\n", ret);
		} else {
			pr_info("Sent %d bytes: %s\n", ret, s_work->message);
		}
	}
release_wait:
	remove_wait_queue(sk_sleep(s_work->sock->sk), &wait);

release_socket:
	if (s_work->sock) {
		sock_release(s_work->sock);
		s_work->sock = NULL;
	}
}

// 模块初始化
static int __init workqueue_socket_init(void)
{
	// 分配工作结构体内存
	s_work = kzalloc(sizeof(struct socket_work), GFP_KERNEL);
	if (!s_work) {
		pr_err("Failed to allocate work struct\n");
		return -ENOMEM;
	}

	// 初始化工作队列项
	INIT_WORK(&s_work->work, socket_worker);

	// 准备消息数据
	s_work->message = kstrdup("Hello from kernel workqueue!", GFP_KERNEL);
	if (!s_work->message) {
		kfree(s_work);
		pr_err("Failed to allocate message\n");
		return -ENOMEM;
	}

	// 调度工作到系统默认工作队列
	schedule_work(&s_work->work);
	pr_info("Work scheduled\n");
	return 0;
}

// 模块退出
static void __exit workqueue_socket_exit(void)
{
	// 等待工作项完成执行
	cancel_work_sync(&s_work->work);

	// 清理资源（worker可能已释放sock，此处检查冗余释放）
	if (s_work->sock) {
		sock_release(s_work->sock);
	}
	kfree(s_work->message);
	kfree(s_work);
	pr_info("Module unloaded\n");
}

module_init(workqueue_socket_init);
module_exit(workqueue_socket_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Workqueue-based Kernel TCP Client");

/* 

# insmod work_queue_socket.ko
[189643.933304] Work scheduled
[189643.937599] Connect failed: -111

# rmmod work_queue_socket.ko
[189814.466340] Module unloaded

❯ nc -l -p 8080

❯ lsof -i:8080
COMMAND    PID  USER FD   TYPE  DEVICE SIZE/OFF NODE NAME
nc      310349 black 3u  IPv4 1008948      0t0  TCP *:http-alt (LISTEN)

# insmod work_queue_socket.ko
[189831.251322] Work scheduled
[189831.254519] Connected to 10.5.8.81:8080
[189831.257185] Sent 28 bytes: Hello from kernel workqueue!


❯ nc -l -p 8080
Hello from kernel workqueue!%

# rmmod work_queue_socket
[189878.293283] Module unloaded

*/
