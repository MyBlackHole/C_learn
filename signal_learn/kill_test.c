// #include <fcntl.h>
#include <signal.h> //含kill()
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int wait_mark;

static void stop()
{
	printf("stop()\n");
	wait_mark = 0;
}

static void waiting()
{
	while (wait_mark != 0) {
		;
	}
}

int demo_kill_main(int argc, const char *argv[])
{
	pid_t p1, p2;
	signal(SIGINT, stop); // 这里被取消注释了

	if ((p1 = fork()) < 0) { // 创建子进程p1
		perror("fork() erron");
		exit(1);
	} else if (p1 == 0) {
		if ((p2 = fork()) < 0) { // 创建子进程p2
			perror("fork() erron");
			exit(1);
		} else if (p2 == 0) {
			// signal(SIGINT,stop);	//接受到^c信号，转到stop函数（这里被注释了）
			kill(p2, 17); // 向p2发送软中断信号17
			// kill(p1, 17); //向p1发送软中断信号17
			// waiting();
			lockf(STDOUT_FILENO, 1, 0);
			printf("Child process2 is killed by parent!\n");
			lockf(STDOUT_FILENO, 0, 0);
			exit(0);
		} else {
			wait_mark = 1;
			signal(17, stop); // 接收到软中断信号16，转到stop函数
			waiting();
			lockf(STDOUT_FILENO, 1, 0);
			printf("Child process1 is killed by parent!\n");
			lockf(STDOUT_FILENO, 0, 0);
			// wait(NULL); //同步
			exit(0);
		}
	} else {
		wait_mark = 1;
		// signal(17, stop); //接收到软中断信号17，转到stop函数
		waiting();
		lockf(STDOUT_FILENO, 1, 0);
		printf("Parent process is killed!\n");
		lockf(STDOUT_FILENO, 0, 0);
		exit(0);
	}
	return 0;
}
