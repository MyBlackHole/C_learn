#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

volatile sig_atomic_t quitflag;

static void sig_int(int signo)
{
	if (signo == SIGINT)
		printf("\n interrupt SIGINT\n");
	else if (signo == SIGQUIT) {
		quitflag = 1;
		printf("\n interrupt SIGQUIT\n");
	}
}
int demo_sigsuspend_main(void)
{
	sigset_t newmask, oldmask, zeromask;
	if (signal(SIGINT, sig_int) == SIG_ERR) {
		perror("signal sigint error");
		exit(1);
	}
	if (signal(SIGQUIT, sig_int) == SIG_ERR) {
		perror("signal sigquit error");
		exit(1);
	}

	// 初始化信号集
	sigemptyset(&zeromask);
	sigemptyset(&newmask);

	// 添加信号到信号集
	sigaddset(&newmask, SIGQUIT);

	// sigsuspend 的另一种应用是等待一个信号处理程序设置一个全局变量，
	// 就是当希望捕捉某信号时，才唤醒主例程。在此往往通过这个全局变量来决定

	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
		perror("SIG_BLOCK error");
		exit(1);
	}
	while (quitflag == 0) {
		sigsuspend(&zeromask);
	}
	quitflag = 0;
	// SIG_SETMASK该进程新的信号屏蔽是set指向的值
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		perror("SIG_SETMASK error");
		exit(1);
	}
	exit(0);
}
