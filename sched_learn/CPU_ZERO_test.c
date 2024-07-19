#define _GNU_SOURCE
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *myfun(void *arg)
{
	cpu_set_t mask;
	cpu_set_t get;
	char buf[256];
	int i;
	int j;
	int num = sysconf(_SC_NPROCESSORS_CONF);
	printf("system has %d processor(s)\n", num);
	for (i = 0; i < num; i++) {
		// 清空一个集合
		CPU_ZERO(&mask);
		// 将给定的cpu号加到集合
		CPU_SET(i, &mask);
		// 使当前线程运行在 mask 所设定的那些CPU上.
		if (pthread_setaffinity_np(pthread_self(), sizeof(mask),
					   &mask) < 0) {
			fprintf(stderr, "set thread affinity failed\n");
		}
		// 清空一个集合
		CPU_ZERO(&get);
		if (pthread_getaffinity_np(pthread_self(), sizeof(get), &get) <
		    0) {
			fprintf(stderr, "get thread affinity failed\n");
		}
		for (j = 0; j < num; j++) {
			// 检查一个CPU号是否在这个集合中
			if (CPU_ISSET(j, &get)) {
				printf("thread %d is running in processor %d\n",
				       (int)pthread_self(), j);
			}
		}
		j = 0;
		while (j++ < 100000000) {
			memset(buf, 0, sizeof(buf));
		}
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t tid;
	if (pthread_create(&tid, NULL, (void *)myfun, NULL) != 0) {
		fprintf(stderr, "thread create failed\n");
		return -1;
	}
	pthread_join(tid, NULL);
	return 0;
}
