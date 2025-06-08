/**
 * @file 条件变量实例2.c
 * @author {BlackHole} ({1358244533@qq.com})
 * @brief
 * @date 2021/08/22 14:44:04
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int travelercount = 0;
pthread_cond_t taxicond_1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t taximutex_1 = PTHREAD_MUTEX_INITIALIZER;

void *traveler_arrive_1(void *name)
{
	char *str_p = (char *)name;

	pthread_mutex_lock(&taximutex_1);

	printf("traveler: %s need a taxi now!\n", str_p);
	travelercount++;
	pthread_cond_wait(&taxicond_1, &taximutex_1);

	pthread_mutex_unlock(&taximutex_1);
	printf("traveler: %s now got a taxi!\n", str_p);
	pthread_exit(NULL);
}

void *taxi_arrive_1(void *name)
{
	char *str_p = (char *)name;
	printf("Taxi: %s arrives.\n", str_p);
	for (;;) {
		if (travelercount) {
			pthread_cond_signal(&taxicond_1);
			travelercount--;
			break;
		}
	}
	pthread_exit(NULL);
}

int demo_cond_signal_main(int argc, char **argv)
{
	char *name;
	pthread_t thread;
	pthread_attr_t threadattr;
	pthread_attr_init(&threadattr);

	name = "Jack";
	pthread_create(&thread, &threadattr, taxi_arrive_1, name);
	sleep(1);
	name = "Susan";
	pthread_create(&thread, &threadattr, traveler_arrive_1, name);
	sleep(3);
	name = "Mike";
	pthread_create(&thread, &threadattr, taxi_arrive_1, name);
	sleep(4);

	return 0;
}
