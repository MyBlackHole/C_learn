/**
 * @file 非堵塞模式.c
 * @author {BlackHole} ({1358244533@qq.com})
 * @brief
 * @date 2021/08/22 14:08:04
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int demo_mutex_timedlock_main(void)
{
	int err;
	struct timespec tout;
	struct tm *tmp;
	char buf[64];

	// 初始化互斥锁
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

	// 加锁
	pthread_mutex_lock(&lock);
	printf("mutex is locked\n");

	// 获取实时时钟
	clock_gettime(CLOCK_REALTIME, &tout);
	tmp = localtime(&tout.tv_sec);
	strftime(buf, sizeof(buf), "%r", tmp);
	printf("current time is %s\n", buf);

	tout.tv_sec += 10;
	// 定时锁
	err = pthread_mutex_timedlock(&lock, &tout);
	// 获取实时时钟
	clock_gettime(CLOCK_REALTIME, &tout);
	tmp = localtime(&tout.tv_sec);
	strftime(buf, sizeof(buf), "%r", tmp);
	printf("the time is now %s\n", buf);

	if (err == 0) {
		printf("mutex locked again\n");
	} else {
		printf("can`t lock mutex again:%s\n", strerror(err));
	}

	// 释放锁
	pthread_mutex_destroy(&lock);

	return 0;
}
