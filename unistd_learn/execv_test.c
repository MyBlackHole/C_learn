#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int demo_execv_main()
{
	printf("调用execv前进程id是%d\n", getpid());

	if (0 == (fork())) {
		char *arg[1] = { NULL };
		execv("/media/black/Data/Documents/C/out/obj/unistd_learn/setsid_test",
		      arg);

		printf("发生异常!");
	} else {
		// 父进程等待子进程结束，并输出
		wait(NULL);
		printf("\n执行完毕，退出\n");
	}
	return EXIT_SUCCESS;
}
