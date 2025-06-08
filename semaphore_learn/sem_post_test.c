// 信号量用于互斥实例
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

sem_t sem; // 信号量

void printer(char *str)
{
	sem_wait(&sem); // 减一，p操作
	while (*str) // 输出字符串（如果不用互斥，此处可能会被其他线程入侵）
	{
		putchar(*str);
		fflush(stdout);
		str++;
		sleep(1);
	}
	printf("\n");

	sem_post(&sem); // 加一，v操作
}

void *thread_fun1(void *arg)
{
	char *str1 = "hello";
	printer(str1);
	return NULL;
}

void *thread_fun2(void *arg)
{
	char *str2 = "world";
	printer(str2);
	return NULL;
}

int demo_sem_post_main(void)
{
	pthread_t tid1, tid2;

	sem_init(&sem, 0, 1); // 初始化信号量，初始值为 1

	// 创建 2 个线程
	pthread_create(&tid1, NULL, thread_fun1, NULL);
	pthread_create(&tid2, NULL, thread_fun2, NULL);

	// 等待线程结束，回收其资源
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	sem_destroy(&sem); // 销毁信号量

	return EXIT_SUCCESS;
}
