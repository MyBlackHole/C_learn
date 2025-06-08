#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// 初始化 once 对象
static pthread_once_t once = PTHREAD_ONCE_INIT;

// 只会运行一次 (单一对象下 once)
void once_run(void)
{
	unsigned int tid = pthread_self();
	printf("once_run in thread %u\n", tid);
}

void *once_test_task1(void *arg)
{
	pthread_t tid = pthread_self();
	printf("thread1 enter %lu\n", tid);
	pthread_once(&once, once_run);
	printf("thread1 returns %lu\n", tid);

	return NULL;
}

void *once_test_task2(void *arg)
{
	pthread_t tid = pthread_self();
	printf("thread2 enter %lu\n", tid);
	pthread_once(&once, once_run);
	printf("thread2 returns %lu\n", tid);

	return NULL;
}

int demo_once_main(int argc, char *argv[])
{
	pthread_t thrd1;
	pthread_t thrd2;

	pthread_create(&thrd1, NULL, (void *)once_test_task1, NULL);
	pthread_create(&thrd2, NULL, (void *)once_test_task2, NULL);

	sleep(5);
	printf("Main thread exit...\n");

	return 0;
}
