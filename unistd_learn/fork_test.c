#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <unistd.h>

int demo_fork_main(void)
{
	int count = 1;
	int child;

	/*// 设置进程名(有用)*/
	/*int ret;*/
	/*char new_name[255];*/
	/*snprintf(new_name, sizeof(new_name), "main_%s_%d_%d",*/
	/*	 "127.0.0.1", 1080, 1);*/
	/*ret = prctl(PR_SET_NAME, new_name);*/
	/*if (ret != 0) {*/
	/*	perror("prctl error : ");*/
	/*}*/

	child = fork();

	if (child < 0) {
		perror("fork error : ");
	} else if (child == 0) {
		// 设置进程名
		int ret;
		char new_name[255];
		char old_name[255];
		snprintf(new_name, sizeof(new_name), "child_%s_%d_%d",
			 "127.0.0.1", 1080, 1);
		ret = prctl(PR_SET_NAME, new_name, NULL, NULL, NULL);
		if (ret != 0) {
			perror("prctl error : ");
		}

		ret = prctl(PR_GET_NAME, old_name);
		if (ret < 0) {
			printf("PR_GET_NAME error");
			exit(EXIT_FAILURE);
		}
		printf("new: %s - %d\n", old_name, getpid());

		sleep(100);
		++count;
		printf("in child process, pid=%d, count=%d (%p)\n", getpid(),
		       count, &count);
	} else {
		++count;
		printf("in parent process, pid=%d, count=%d (%p)\n", getpid(),
		       count, &count);
	}

	printf("pid=%d quit now...\n", getpid());
	// 等待子进程结束
	wait(NULL);
	return EXIT_SUCCESS;
}

/*int demo_fork_main(char argc[], int argv)*/
/*{*/
/*	unsigned int i = 0;*/
/*	unsigned int pid1, pid2;*/
/**/
/*	if (0 == fork()) {*/
/*		prctl(PR_SET_NAME, "Child", NULL, NULL, NULL);*/
/*		for (;;) {*/
/*			for (i = 0; i < 100000; i++)*/
/*				;*/
/*			pid1 = getpid();*/
/*			printf("This is the child process,process id is %d",*/
/*			       pid1);*/
/*		}*/
/*	} else {*/
/*		prctl(PR_SET_NAME, "Child", NULL, NULL, NULL);*/
/*		for (;;) {*/
/*			for (i = 0; i < 100000; i++)*/
/*				;*/
/*			pid1 = getpid();*/
/*			printf("This is the child process,process id is %d",*/
/*			       pid1);*/
/*		}*/
/*	}*/
/*	return 0;*/
/*}*/
