#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <unistd.h>

#define SECONDS 10

int demo_PR_SET_PDEATHSIG_main(void)
{
	pid_t pid;
	// fork一个进程
	pid = fork();
	// 创建失败
	if (pid < 0) {
		perror("fork error:");
		exit(1);
	}
	// 子进程
	if (pid == 0) {
		/*父进程退出时，会收到SIGKILL信号*/
		// 跟随父进程退出
		prctl(PR_SET_PDEATHSIG, SIGKILL);
		printf("child process.\n");
		printf("child pid:%d, parent pid:%d\n", getpid(), getppid());
		printf("sleep 10 seconds.\n");
		// sleep一段时间，让父进程先退出，为了便于观察，sleep10s
		sleep(SECONDS);

		printf("nowchild pid:%d, parent pid:%d\n", getpid(), getppid());
	}
	// 父进程
	else {
		printf("parent process.\n");
		sleep(1);
	}
	return EXIT_SUCCESS;
}
