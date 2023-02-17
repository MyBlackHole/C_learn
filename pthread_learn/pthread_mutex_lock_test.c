#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 初始化互斥锁 */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* 初始化条件变量 */
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int i = 1;

void *thread1(void *);
void *thread2(void *);

int main()
{
    pthread_t t_a;
    pthread_t t_b;

    pthread_create(&t_a, NULL, thread1, NULL);
    pthread_create(&t_b, NULL, thread2, NULL);

    printf("t_a:0x%lx, t_b:0x%lx\n", t_a, t_b);
    pthread_join(t_b, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    exit(0);
}

void *thread1(void *junk)
{
    for (i = 1; i <= 9; i++)
    {
        pthread_mutex_lock(&mutex);
        printf("call thread1 \n");
        if (i % 3 == 0)
        {
            pthread_cond_signal(&cond);
            printf("thread1: ***** i=%d\n", i);
        }
        else
        {
            printf("thread1: %d\n", i);
        }

        pthread_mutex_unlock(&mutex);

        printf("thread1: sleep i=%d\n", i);
        sleep(1);
        printf("thread1: sleep i=%d ***** end\n", i);
    }
    return 0;
}

void *thread2(void *junk)
{
    while (i <= 9)
    {
        pthread_mutex_lock(&mutex);
        printf("call thread2 \n");
        if (i % 3 != 0)
        {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("thread2: %d\n", i);

        pthread_mutex_unlock(&mutex);

        printf("thread2: sleep i=%d\n", i);
        sleep(1);
        printf("thread2: sleep i=%d ***** end\n", i);
    }
    return 0;
}
