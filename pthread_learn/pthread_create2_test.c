#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREAD 100

void *thread_inc_2_1(void *arg);
void *thread_des_2_1(void *arg);
long long num_3 = 0;

int demo_create2_main(int argc, char *argv[])
{
    pthread_t thread_id[NUM_THREAD];
    int index;

    printf("sizeof long long: %lu \n", sizeof(long long));
    for (index = 0; index < NUM_THREAD; index++)
    {
        if (index % 2)
        {
            pthread_create(&(thread_id[index]), NULL, thread_inc_2_1, NULL);
        }
        else
        {
            pthread_create(&(thread_id[index]), NULL, thread_des_2_1, NULL);
        }
    }

    for (index = 0; index < NUM_THREAD; index++) 
    {
        pthread_join(thread_id[index], NULL);
    }

    printf("result: %lld \n", num_3);
    return 0;
}

void *thread_inc_2_1(void *arg)
{
    int i;
    for (i = 0; i < 50000000; i++) {
        num_3 += 1;
    } 
    return NULL;
}
void *thread_des_2_1(void *arg)
{
    int i;
    for (i = 0; i < 50000000; i++) 
    {
        num_3 -= 1;
    }
    return NULL;
}
