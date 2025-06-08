#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void sig_ids(int signo)
{
	printf("SIGHUP received,pid=%ld\n", (long)getpid());
}
static void pr_ids(char *name)
{
	// 分别获取进程组id父进程id，进程组id前台进程组id
	printf("%s :pid =%ld,ppid=%ld,pgid=%ld,tpgrp=%ld\n", name,
	       (long)getpid(), (long)getppid(), (long)getpgrp(),
	       (long)tcgetpgrp(STDIN_FILENO));
	// 刷新缓冲区
	fflush(stdout);
}

int demo_signal1_main(void)
{
	char c;
	pid_t pid;
	pr_ids("parent");
	if ((pid = fork()) < 0) {
		perror("fork error");
		exit(1);
	} else if (pid > 0) {
		sleep(5);
	} else {
		pr_ids("child");
		signal(SIGHUP, sig_ids);
		kill(getpid(), SIGTSTP);
		pr_ids("child");
		if (read(STDIN_FILENO, &c, 1) != 1) {
			printf("read error %d on contralling TTY\n", errno);
		}
	}
	exit(0);
}
