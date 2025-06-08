#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SECONDS10 10
#define SECONDS1 1

static void *thread_main(void *arg);

int demo_create1_main(int argc, char *argv[])
{
	pthread_t t_id;
	int thread_param = 5;
	// 请求创建一个线程，从 thread_main 调用开始，在单独的执行流中运行。同时传
	// 参数
	if (pthread_create(&t_id, NULL, thread_main, (void *)&thread_param) !=
	    0) {
		puts("pthread_create() error");
		return EXIT_FAILURE;
	}

	// 延迟进程终止时间
	sleep(SECONDS10);
	puts("end of main");
	return EXIT_SUCCESS;
}

// 传入的参数是 pthread_create 的第四个
void *thread_main(void *arg)
{
	/*int index;*/
	int cnt = *((int *)arg);
	for (int index = 0; index < cnt; index++) {
		sleep(SECONDS1);
		puts("running thread");
	}
	return NULL;
}
