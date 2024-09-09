#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

int demo_fork_test_main(int argc, const char *argv[])
{
	int pid = 0;
	sem_t sem;
	int ret = 0;

	// 需要使用共享内存处理
	// fork 后，sem 变量在子进程和父进程中都有一份拷贝，因此需要使用共享内存处理
	ret = sem_init(&sem, 1, 1); /* 初始化信号量的值为1 */
	printf("ret = %d\n", ret);

	pid = fork();

	if (pid == 0) { /* 子进程 */
		printf("I'm child\n");
		printf("child sem_wait...\n");
		sem_wait(&sem);
		printf("child sem_wait ok\n");
	} else if (pid > 0) { /* 父进程 */
		sleep(1);
		printf("I'm parent\n");
		printf("parent sem_wait...\n");
		sem_wait(&sem);
		printf("parent sem_wait ok\n");
	}

	return EXIT_SUCCESS;
}
