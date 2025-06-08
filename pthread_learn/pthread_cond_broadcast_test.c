#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static pthread_cond_t cond;
static pthread_mutex_t mutex1;
static pthread_mutex_t mutex2;

void *thread1_entry(void *arg)
{
	while (1) {
		pthread_mutex_lock(&mutex1);
		printf("cond wait cond1\n");
		pthread_cond_wait(&cond, &mutex1);
		printf("recv cond1\n");
		sleep(3);
		pthread_mutex_unlock(&mutex1);
	}
}

void *thread2_entry(void *arg)
{
	while (1) {
		// pthread_mutex_lock(&mutex1);
		pthread_mutex_lock(&mutex2);
		printf("cond wait cond2\n");
		// pthread_cond_wait(&cond, &mutex1);
		pthread_cond_wait(&cond, &mutex2);
		printf("recv cond2\n");
		sleep(3);
		// pthread_mutex_unlock(&mutex1);
		pthread_mutex_unlock(&mutex2);
	}
}

void *thread3_entry(void *arg)
{
	int ret;
	while (1) {
		pthread_mutex_lock(&mutex1);
		pthread_mutex_lock(&mutex2);
		// 唤醒所有wait的条件变量
		// 对于等待同一互斥量的线程只会唤醒先 wait 那个
		ret = pthread_cond_broadcast(&cond);
		if (ret < 0) {
			printf("pthread_cond_broadcast error\n");
		}
		pthread_mutex_unlock(&mutex2);
		pthread_mutex_unlock(&mutex1);
		sleep(2);
	}
}

int demo_cond_broadcast_main(void)
{
	int ret = 0;
	pthread_t tid1;
	pthread_t tid2;
	pthread_t tid3;
	// 初始化条件变量
	ret = pthread_cond_init(&cond, NULL);
	if (ret < 0) {
		printf("pthread_cond_init error\n");
	}

	// 初始化互斥量
	ret = pthread_mutex_init(&mutex1, NULL);
	if (ret < 0) {
		printf("pthread_mutex_init error\n");
	}

	// 初始化互斥量
	ret = pthread_mutex_init(&mutex2, NULL);
	if (ret < 0) {
		printf("pthread_mutex_init error\n");
	}

	// 创建线程
	ret = pthread_create(&tid1, NULL, thread1_entry, NULL);
	if (ret < 0) {
		printf("pthread_create thread1 error\n");
	}

	// 创建线程
	ret = pthread_create(&tid2, NULL, thread2_entry, NULL);
	if (ret < 0) {
		printf("pthread_create thread2 error\n");
	}
	sleep(2);

	// 创建线程
	ret = pthread_create(&tid3, NULL, thread3_entry, NULL);
	if (ret < 0) {
		printf("pthread_create thread3 error\n");
	}
#if 0
        pthread_mutex_lock(&mutex1);
        pthread_mutex_lock(&mutex2);
        ret = pthread_cond_broadcast(&cond);
        if(ret < 0)
        {
                printf("pthread_cond_broadcast error\n");
        }
        pthread_mutex_unlock(&mutex1);
        pthread_mutex_unlock(&mutex2);
#endif

	while (1) {
		sleep(10000);
	}
	return 0;
}
