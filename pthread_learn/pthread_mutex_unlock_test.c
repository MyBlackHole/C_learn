#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREAD 100
void *thread_inc_2(void *arg);
void *thread_des_2(void *arg);

long long num = 0;
pthread_mutex_t mutex_1;  // 保存互斥量读取值的变量

int demo_mutex_unlock_main(int argc, char *argv[])
{
    pthread_t thread_id[NUM_THREAD];
    int index;

    pthread_mutex_init(&mutex_1, NULL);  // 创建互斥量

    for (index = 0; index < NUM_THREAD; index++)
    {
        if (index % 2)
        {

            pthread_create(&(thread_id[index]), NULL, thread_inc_2, NULL);
        }
        else
        {

            pthread_create(&(thread_id[index]), NULL, thread_des_2, NULL);
        }
    }

    for (index = 0; index < NUM_THREAD; index++) 
    {
        pthread_join(thread_id[index], NULL);
    }

    printf("result: %lld \n", num);
    pthread_mutex_destroy(&mutex_1);  // 销毁互斥量
    return 0;
}

void *thread_inc_2(void *arg)
{
    int index;
    pthread_mutex_lock(&mutex_1);  // 上锁
    for (index = 0; index < 50000000; index++) 
    {
        num += 1;
    }
    pthread_mutex_unlock(&mutex_1);  // 解锁
    return NULL;
}
void *thread_des_2(void *arg)
{
    int index;
    pthread_mutex_lock(&mutex_1);
    for (index = 0; index < 50000000; index++) {
        num -= 1;
    }
    pthread_mutex_unlock(&mutex_1);
    return NULL;
}
