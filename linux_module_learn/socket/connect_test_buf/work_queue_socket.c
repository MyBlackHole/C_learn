#include "linux/slab.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/net.h>
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

// 定义工作结构体，包含 socket 和消息数据
struct socket_work {
	struct work_struct work;
	struct socket *sock;
	char *message;
};

static struct socket_work *s_work;

// 工作处理函数（异步执行连接和发送）
static void socket_worker(struct work_struct *work)
{
	struct socket_work *s_work =
		container_of(work, struct socket_work, work);
	struct sockaddr_in sin;
	int ret;

	// 1. 创建 TCP socket
	ret = sock_create_kern(&init_net, AF_INET, SOCK_STREAM, IPPROTO_TCP,
			       &s_work->sock);
	if (ret < 0) {
		pr_err("Failed to create socket: %d\n", ret);
		goto out;
	}

	// 2. 设置目标地址
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(target_port);
	sin.sin_addr.s_addr = in_aton(target_ip);

	// 3. 发起连接（可能阻塞）
	ret = s_work->sock->ops->connect(s_work->sock, (struct sockaddr *)&sin,
					 sizeof(sin), 0);
	if (ret < 0) {
		pr_err("Connect failed: %d\n", ret);
		goto release_socket;
	}

	pr_info("Connected to %s:%d\n", target_ip, target_port);

	// 4. 发送数据
	{
		struct kvec vec = { .iov_base = s_work->message,
				    .iov_len = strlen(s_work->message) };
		struct msghdr msg_hdr = { .msg_flags = 0 };
		pr_info("vec.iov_len = %ld\n", vec.iov_len);
		ret = kernel_sendmsg(s_work->sock, &msg_hdr, &vec, 1,
				     vec.iov_len);
		if (ret < 0) {
			pr_err("Send failed: %d\n", ret);
		} else {
			pr_info("Sent %d\n", ret);
			/*pr_info("Sent %d bytes: %s\n", ret, s_work->message);*/
		}
	}

release_socket:
	if (s_work->sock) {
		sock_release(s_work->sock);
		s_work->sock = NULL;
	}
out:
	vfree(s_work->message);
	s_work->message = NULL;
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

	s_work->message = vmalloc(1024 * 1024 * 10);
	/*// 准备消息数据*/
	/*s_work->message = kstrdup("Hello from kernel workqueue!", GFP_KERNEL);*/
	if (!s_work->message) {
		kfree(s_work);
		pr_err("Failed to allocate message\n");
		return -ENOMEM;
	}
	memset(s_work->message, 'a', 1024 * 1024 * 10);
	s_work->message[1024 * 1024 * 10 - 1] = '\0';

	// 调度工作到系统默认工作队列
	schedule_work(&s_work->work);
	pr_info("Work scheduled\n");
	return 0;
}

// 模块退出
static void __exit workqueue_socket_exit(void)
{
	pr_info("cancel_work_sync\n");
	// 等待工作项完成执行
	cancel_work_sync(&s_work->work);

	pr_info("sock_release\n");
	// 清理资源（worker可能已释放sock，此处检查冗余释放）
	if (s_work->sock) {
		sock_release(s_work->sock);
	}
	pr_info("kfree\n");
	if (s_work->message)
		vfree(s_work->message);
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
