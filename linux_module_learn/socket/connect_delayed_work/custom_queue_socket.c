#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/net.h>
#include <linux/in.h>
#include <linux/inet.h>
#include <linux/socket.h>
#include <linux/workqueue.h>
#include <linux/timer.h>

#define TARGET_IP "10.5.8.81" // 目标服务器IP
static char *target_ip = TARGET_IP;
module_param(target_ip, charp, 0644);
MODULE_PARM_DESC(target_ip, "Target IP address");
#define TARGET_PORT 8080 // 目标端口
static int target_port = TARGET_PORT;
module_param(target_port, int, 0644);
MODULE_PARM_DESC(target_port, "Target port number");
#define MAX_RETRIES 3 // 最大重试次数
#define CONNECT_TIMEOUT_MS 5000 // 连接超时时间（毫秒）

// 定义工作结构体，包含 socket、消息、重试计数和定时器
struct socket_work {
	struct delayed_work dwork; // 延迟工作项（支持超时重试）
	struct socket *sock;
	char *message;
	int retries;
	struct timer_list timeout_timer; // 超时定时器
};

static struct workqueue_struct *custom_wq; // 自定义工作队列

// 超时处理函数（定时器回调）
static void timeout_handler(struct timer_list *t)
{
	struct socket_work *s_work = from_timer(s_work, t, timeout_timer);
	pr_err("Connection timeout! Retries left: %d\n",
	       MAX_RETRIES - s_work->retries);

	// 取消当前socket操作（若仍在进行）
	if (s_work->sock) {
		kernel_sock_shutdown(s_work->sock, SHUT_RDWR);
		sock_release(s_work->sock);
		s_work->sock = NULL;
	}

	// 重新调度任务（延迟1秒后重试）
	if (s_work->retries < MAX_RETRIES) {
		s_work->retries++;
		queue_delayed_work(custom_wq, &s_work->dwork,
				   msecs_to_jiffies(1000));
	} else {
		pr_err("Max retries reached. Aborting.\n");
		kfree(s_work->message);
		kfree(s_work);
	}
}

// 工作处理函数（连接和发送数据）
static void socket_worker(struct work_struct *work)
{
	struct socket_work *s_work =
		container_of(work, struct socket_work, dwork.work);
	struct sockaddr_in sin;
	int ret;

	// 1. 创建 TCP socket
	ret = sock_create_kern(&init_net, AF_INET, SOCK_STREAM, IPPROTO_TCP,
			       &s_work->sock);
	if (ret < 0) {
		pr_err("Failed to create socket: %d\n", ret);
		goto retry_or_abort;
	}

	// 2. 设置目标地址
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(target_port);
	sin.sin_addr.s_addr = in_aton(target_ip);

	// 3. 启动超时定时器
	timer_setup(&s_work->timeout_timer, timeout_handler, 0);
	mod_timer(&s_work->timeout_timer,
		  jiffies + msecs_to_jiffies(CONNECT_TIMEOUT_MS));

	// 4. 发起非阻塞连接
	ret = s_work->sock->ops->connect(s_work->sock, (struct sockaddr *)&sin,
					 sizeof(sin), O_NONBLOCK);
	if (ret == -EINPROGRESS) {
		// 异步等待连接完成（此处简化处理，实际需用异步I/O或等待队列）
		pr_info("Connection in progress...\n");
		return;
	} else if (ret < 0) {
		pr_err("Connect failed: %d\n", ret);
		goto cleanup;
	}

	// 5. 发送数据
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
			del_timer(&s_work->timeout_timer); // 成功则取消定时器
		}
	}

cleanup:
	if (s_work->sock) {
		sock_release(s_work->sock);
		s_work->sock = NULL;
	}

retry_or_abort:
	if (ret < 0 && s_work->retries < MAX_RETRIES) {
		s_work->retries++;
		queue_delayed_work(custom_wq, &s_work->dwork,
				   msecs_to_jiffies(1000));
	} else if (ret >= 0) {
		kfree(s_work->message);
		kfree(s_work);
	} else {
		pr_err("Operation failed after %d retries\n", MAX_RETRIES);
		kfree(s_work->message);
		kfree(s_work);
	}
}

// 模块初始化
static int __init custom_queue_socket_init(void)
{
	struct socket_work *s_work;

	// 创建自定义工作队列（并发度1，高优先级）
	custom_wq =
		alloc_workqueue("net_clients", WQ_MEM_RECLAIM | WQ_HIGHPRI, 1);
	if (!custom_wq) {
		pr_err("Failed to create workqueue\n");
		return -ENOMEM;
	}

	// 初始化工作项
	s_work = kzalloc(sizeof(struct socket_work), GFP_KERNEL);
	if (!s_work) {
		destroy_workqueue(custom_wq);
		return -ENOMEM;
	}

	s_work->message =
		kstrdup("Hello from kernel with custom queue!", GFP_KERNEL);
	if (!s_work->message) {
		kfree(s_work);
		destroy_workqueue(custom_wq);
		return -ENOMEM;
	}

	s_work->retries = 0;
	INIT_DELAYED_WORK(&s_work->dwork, socket_worker);

	// 提交任务到自定义队列
	queue_delayed_work(custom_wq, &s_work->dwork, 0);
	pr_info("Work queued\n");
	return 0;
}

// 模块退出
static void __exit custom_queue_socket_exit(void)
{
	// 清空队列并销毁
	flush_workqueue(custom_wq);
	destroy_workqueue(custom_wq);
	pr_info("Module unloaded\n");
}

module_init(custom_queue_socket_init);
module_exit(custom_queue_socket_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Custom Queue + Timeout Kernel TCP Client");
