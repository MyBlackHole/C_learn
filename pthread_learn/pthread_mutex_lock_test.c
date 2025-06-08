#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 初始化互斥锁 */
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* 初始化条件变量 */
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int index = 1;

void *thread_3(void *);
void *thread_4(void *);

int demo_mutex_lock_main()
{
	pthread_t t_a;
	pthread_t t_b;

	pthread_create(&t_a, NULL, thread_3, NULL);
	pthread_create(&t_b, NULL, thread_4, NULL);

	printf("t_a:0x%lx, t_b:0x%lx\n", t_a, t_b);
	pthread_join(t_b, NULL);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);

	exit(0);
}

void *thread_3(void *junk)
{
	for (index = 1; index <= 9; index++) {
		pthread_mutex_lock(&mutex);
		printf("call thread1 \n");
		if (index % 3 == 0) {
			pthread_cond_signal(&cond);
			printf("thread1: ***** i=%d\n", index);
		} else {
			printf("thread1: %d\n", index);
		}

		pthread_mutex_unlock(&mutex);

		printf("thread1: sleep i=%d\n", index);
		sleep(1);
		printf("thread1: sleep i=%d ***** end\n", index);
	}
	return 0;
}

void *thread_4(void *junk)
{
	while (index <= 9) {
		pthread_mutex_lock(&mutex);
		printf("call thread2 \n");
		if (index % 3 != 0) {
			pthread_cond_wait(&cond, &mutex);
		}

		printf("thread2: %d\n", index);

		pthread_mutex_unlock(&mutex);

		printf("thread2: sleep i=%d\n", index);
		sleep(1);
		printf("thread2: sleep i=%d ***** end\n", index);
	}
	return 0;
}
