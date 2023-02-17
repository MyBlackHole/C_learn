#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define COUNT 10000

static int i;

void *thread_func(void *arg)
{
    for (int j = 0; j < COUNT; j++)
    {
        i++;
    }
    pthread_exit(0);
}

int main(void)
{
    pthread_t tid1;
    pthread_t tid2;

    pthread_create(&tid1, NULL, thread_func, NULL);
    pthread_create(&tid2, NULL, thread_func, NULL);
    printf("pthread tid1=%lu; pthread tid1=%lu\n", tid1, tid2);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("%d\n", i);
    return 0;
}
