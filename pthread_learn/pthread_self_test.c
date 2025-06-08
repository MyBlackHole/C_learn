#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *get_pthread_id(void *arg)
{
	printf("get_pthread_id pthread id=%lu\n", pthread_self());
	return arg;
}

int demo_self_main(void)
{
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	printf("process id=%d\n", pid);

	pthread_create(&tid, NULL, get_pthread_id, NULL);
	printf("pthread id=%lu\n", tid);
	pthread_join(tid, NULL);
	return 0;
}
