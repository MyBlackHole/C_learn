#include <pthread.h>
#include <signal.h>
#include <stdio.h>

static void sig_alrm(int signo);
static void sig_init(int signo);
int demo_sigwait_main()
{
	sigset_t set;
	int sig;
	sigemptyset(&set);
	sigaddset(&set, SIGALRM);
	pthread_sigmask(SIG_SETMASK, &set, NULL); // 阻塞SIGALRM信号

	signal(SIGALRM, sig_alrm);
	signal(SIGINT, sig_init);
	sigwait(&set,
		&sig); // sigwait只是从未决队列中删除该信号，并不改变信号掩码。也就是，当sigwait函数返回，它监听的信号依旧被阻塞。
	switch (sig) {
	case 14:
		printf("sigwait, receive signal SIGALRM\n");
		/*do the job when catch the sigwait*/
		break;
	default:
		break;
	}
	sigdelset(&set, SIGALRM);
	pthread_sigmask(SIG_SETMASK, &set, NULL);

	for (;;) {
	}
	return 0;
}

static void sig_alrm(int signo)
{
	printf("after sigwait, catch SIGALRM\n");
	fflush(stdout);
	return;
}

static void sig_init(int signo)
{
	printf("catch SIGINT\n");
	return;
}
