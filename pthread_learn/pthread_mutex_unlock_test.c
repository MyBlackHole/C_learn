#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREAD 100

long long num = 0;
static pthread_mutex_t mutex; // 保存互斥量读取值的变量

void *mutex_test1(void *arg)
{
	int index;
	pthread_mutex_lock(&mutex); // 上锁
	for (index = 0; index < 50000000; index++) {
		num += 1;
	}
	pthread_mutex_unlock(&mutex); // 解锁
	return NULL;
}
void *mutex_test2(void *arg)
{
	int index;
	pthread_mutex_lock(&mutex);
	for (index = 0; index < 50000000; index++) {
		num -= 1;
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int demo_mutex_unlock_main(int argc, char *argv[])
{
	pthread_t thread_id[NUM_THREAD];
	int index;

	pthread_mutex_init(&mutex, NULL); // 创建互斥量

	for (index = 0; index < NUM_THREAD; index++) {
		if (index % 2) {
			pthread_create(&(thread_id[index]), NULL, mutex_test1,
				       NULL);
		} else {
			pthread_create(&(thread_id[index]), NULL, mutex_test2,
				       NULL);
		}
	}

	for (index = 0; index < NUM_THREAD; index++) {
		pthread_join(thread_id[index], NULL);
	}

	printf("result: %lld \n", num);
	pthread_mutex_destroy(&mutex); // 销毁互斥量
	return 0;
}
