#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex_3;
pthread_cond_t cond;

// 使用宏初始化互斥锁与条件变量
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int index_3 = 1;

void *thread_1(void *junk)
{
	for (index_3 = 1; index_3 <= 9; index_3++) {
		printf("IN one\n");
		pthread_mutex_lock(&mutex_3); //
		if (index_3 % 3 == 0) {
			pthread_cond_signal(
				&cond); /*条件改变，发送信号，通知t_b进程*/
		} else {
			printf("thead1:%d\n", index_3);
		}
		pthread_mutex_unlock(&mutex_3); //*解锁互斥量*/
		printf("Up Mutex\n");
		sleep(10);
	}
	pthread_exit(NULL);
}

void *thread_2(void *junk)
{
	while (index_3 < 9) {
		printf("IN two \n");
		pthread_mutex_lock(&mutex_3);
		if (index_3 % 3 != 0) {
			pthread_cond_wait(&cond, &mutex_3); /*等待*/
		}
		printf("thread2:%d\n", index_3);
		pthread_mutex_unlock(&mutex_3);
		printf("Down Mutex\n");
		sleep(10);
	}
	pthread_exit(NULL);
}

int demo_cond_init_main(void)
{
	pthread_t t_a;
	pthread_t t_b;

	// 使用init方法初始化条件变量与互斥量
	pthread_cond_init(&cond, NULL);
	pthread_mutex_init(&mutex_3, NULL);

	pthread_create(&t_a, NULL, thread_1, NULL); /*创建线程t_a*/
	pthread_create(&t_b, NULL, thread_2, NULL); /*创建线程t_b*/
	pthread_join(t_b, NULL); /*等待线程t_b结束*/
	pthread_mutex_destroy(&mutex_3);
	pthread_cond_destroy(&cond);
	exit(0);
}
