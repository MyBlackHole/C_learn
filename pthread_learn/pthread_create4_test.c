#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define COUNT 10000

static void *thread_func(void *arg)
{
	// time_t start_time;
	// time_t current_time;
	// start_time = time(NULL);
	for (;;) {
		// current_time = time(NULL);
		// if (current_time - start_time > 10)
		// {
		//     break;
		// }
		// printf("%ld --- %ld\n", current_time, (current_time - start_time));
	}
	pthread_exit(EXIT_SUCCESS);
}

// 测试一个进程
// 多个线程可以占用所有 cpu
// 结果：
// 不行 (出现接近 200%, 可能是超线程导致的)(需要达到 200% 需要两个线程以上)(也就是说一个进程只能使用一个物理核心资源)
//
// 2024-02-19
// 可以通过多线程占用所有 cpu 资源
// 上一次测试循环里使用了 time 系统调用导致测试结果不对
int demo_create4_main(void)
{
	pthread_t tid1;
	pthread_t tid2;
	pthread_t tid3;
	pthread_t tid4;

	pthread_create(&tid1, NULL, thread_func, NULL);
	pthread_create(&tid2, NULL, thread_func, NULL);
	pthread_create(&tid3, NULL, thread_func, NULL);
	pthread_create(&tid4, NULL, thread_func, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	pthread_join(tid4, NULL);
	return EXIT_SUCCESS;
}
