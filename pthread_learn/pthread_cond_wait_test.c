/**
 * @file 条件变量实例1.c
 * @author {BlackHole} ({1358244533@qq.com})
 * @brief
 * @date 2021/08/22 14:38:04
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 条件变量初始化
// 线程同步
pthread_cond_t taxicond = PTHREAD_COND_INITIALIZER;

// 互斥锁初始化
pthread_mutex_t taximutex = PTHREAD_MUTEX_INITIALIZER;

void *traveler_arrive(void *name)
{
	char *str_p = (char *)name;

	printf("Travelr: %s need a taxi now!\n", str_p);
	// 加锁，把信号量加入队列，释放信号量
	pthread_mutex_lock(&taximutex);

	// 堵塞在 taxicond
	// 进入时解开 taximutex
	// 出来时再次获得 taximutex
	pthread_cond_wait(&taxicond, &taximutex);
	pthread_mutex_unlock(&taximutex);
	printf("traveler: %s now got a taxi!\n", str_p);
	pthread_exit(NULL);
}

void *taxi_arrive(void *name)
{
	char *str_p = (char *)name;

	printf("Taxi: %s arrives.\n", str_p);
	// 给线程或者条件发信号，一定要在改变条件状态后再给线程发信号
	pthread_cond_signal(&taxicond);
	pthread_exit(NULL);
}

int demo_cond_wait_main(int argc, char **argv)
{
	char *name;
	pthread_t thread;
	pthread_attr_t threadattr; // 线程属性
	pthread_attr_init(&threadattr); // 线程属性初始化

	// 创建三个线程
	name = "Jack";
	pthread_create(&thread, &threadattr, taxi_arrive, (void *)name);
	sleep(1);
	name = "Susan";
	pthread_create(&thread, &threadattr, traveler_arrive, (void *)name);
	sleep(1);
	name = "Mike";
	pthread_create(&thread, &threadattr, taxi_arrive, (void *)name);
	sleep(1);

	return 0;
}
