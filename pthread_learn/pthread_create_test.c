#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thread_func_3(void *arg)
{
	printf("thread id=%lu\n", pthread_self());
	return arg;
}

int demo_create_main(void)
{
	pthread_t tid;

	pthread_create(&tid, NULL, thread_func_3, NULL);
	printf("pthread id=%lu\n", tid);
	pthread_join(tid, NULL);
	return 0;
}
