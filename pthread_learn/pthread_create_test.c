#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thread_func(void *arg)
{
    printf("thread id=%lu\n", pthread_self());
    return arg;
}

int main(void)
{
    pthread_t tid;

    pthread_create(&tid, NULL, thread_func, NULL);
    printf("pthread id=%lu\n", tid);
    pthread_join(tid, NULL);
    return 0;
}
