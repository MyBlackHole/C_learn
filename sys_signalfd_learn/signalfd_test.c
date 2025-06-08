#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signalfd.h>
#include <unistd.h>

/* fd: -1 生成新文件描述符；或者指定存在有效的 fd ，而 mask
 * 会替换掉之前相关联的信号集。 */
/* mask: 这个文件描述符接受的信号集，可以通过sigsetops()宏初始化。 */
/* int signalfd(int fd, const sigset_t*mask, intflags); */

#define handle_error(msg)           \
	do {                        \
		perror(msg);        \
		exit(EXIT_FAILURE); \
	} while (0)

// ./out/obj/sys_signalfd_learn/signalfd_test
// 1633334
// Got SIGQUIT
// kill -QUIT 1633334
int demo_signalfd_main(void)
{
	printf("%d\n", getpid());
	int sfd;
	ssize_t ret;
	struct signalfd_siginfo fdsi;

	sigset_t mask;
	// 信号清零
	sigemptyset(&mask);

	// 添加信号到掩码集
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);

	// 设置该进程为对应的信号集的内容（当前已经的信号集合做并集、交集、覆盖）
	// 这行代码才是真正的信号设置；
	// 设置屏蔽信号集
	if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1) {
		handle_error("sigprocmask");
	}

	sfd = signalfd(-1, &mask, 0);
	if (sfd == -1) {
		handle_error("signalfd");
	}

	while (1) {
		// 读取发生的信号
		ret = read(sfd, &fdsi, sizeof(struct signalfd_siginfo));
		if (ret != sizeof(struct signalfd_siginfo)) {
			handle_error("read");
		}

		if (fdsi.ssi_signo == SIGINT) {
			printf("Got SIGINT\n");
		} else if (fdsi.ssi_signo == SIGQUIT) {
			printf("Got SIGQUIT\n");
			exit(EXIT_SUCCESS);
		} else {
			printf("Read unexpected signal\n");
		}
	}

	return 0;
}
