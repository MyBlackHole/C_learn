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
pthread_cond_t taxicond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t taximutex = PTHREAD_MUTEX_INITIALIZER;

void *traveler_arrive(void *name)
{
    char *p = (char *)name;

    pthread_mutex_lock(&taximutex);

    printf("traveler: %s need a taxi now!\n", p);
    travelercount++;
    pthread_cond_wait(&taxicond, &taximutex);

    pthread_mutex_unlock(&taximutex);
    printf("traveler: %s now got a taxi!\n", p);
    pthread_exit(NULL);
}

void *taxi_arrive(void *name)
{
    char *p = (char *)name;
    printf("Taxi: %s arrives.\n", p);
    for (;;)
    {
        if (travelercount)
        {
            pthread_cond_signal(&taxicond);
            travelercount--;
            break;
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    char *name;
    pthread_t thread;
    pthread_attr_t threadattr;
    pthread_attr_init(&threadattr);

    name = "Jack";
    pthread_create(&thread, &threadattr, taxi_arrive, name);
    sleep(1);
    name = "Susan";
    pthread_create(&thread, &threadattr, traveler_arrive, name);
    sleep(3);
    name = "Mike";
    pthread_create(&thread, &threadattr, taxi_arrive, name);
    sleep(4);

    return 0;
}
