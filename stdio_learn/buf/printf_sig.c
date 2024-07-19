#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

long fork_cnt = 0;
long handler_cnt = 0;

void sigchld_handler(int sig)
{
	/* 回收僵死子进程，以免产生内存泄漏 */
	while (waitpid(-1, NULL, 0) > 0) {
		/* 在信号处理程序中频繁调用printf() */
		printf("Handler reaped a child process, total:%ld\n",
		       ++handler_cnt);
	}
}

int demo_printf_sig_bug_main()
{
	/* 子进程结束时会向父进程发送SIGCHLD信号，父进程接收到SIGCHLD的默认行为是忽略这个信号
     */
	/* 这里我们设置父进程收到SIGCHLD信号时的行为是调用信号处理程序sigchld_handler
     */
	signal(SIGCHLD, sigchld_handler);
	/* 主程序不断产生子进程，子进程结束后会发送给父进程SIGCHLD信号 */
	while (1) {
		if (fork() == 0) {
			/* 子进程什么都不做，直接结束 */
			exit(0);
		}
		/* 在父进程中频繁调用printf() */
		printf("Parent created a child process, total:%ld\n",
		       ++fork_cnt);
	}
	exit(0);
}
