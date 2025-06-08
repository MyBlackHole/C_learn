// 信号量用于同步实例
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

sem_t sem_g, sem_p; // 定义两个信号量
char char_itme = 'a';

void *pthread_g(void *arg) // 此线程改变字符ch的值
{
	while (1) {
		sem_wait(&sem_g);
		char_itme++;
		sleep(1);
		sem_post(&sem_p);
	}
}

void *pthread_p(void *arg) // 此线程打印ch的值
{
	while (1) {
		sem_wait(&sem_p);
		printf("%c", char_itme);
		fflush(stdout);
		sem_post(&sem_g);
	}
}

int demo_sem_wait_main(int argc, char *argv[])
{
	pthread_t tid1, tid2;
	sem_init(&sem_g, 0, 0); // 初始化信号量为0
	sem_init(&sem_p, 0, 1); // 初始化信号量为1

	// 创建两个线程
	pthread_create(&tid1, NULL, pthread_g, NULL);
	pthread_create(&tid2, NULL, pthread_p, NULL);

	// 回收线程
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return EXIT_SUCCESS;
}
