#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thread_func_3_1(void *arg)
{
    printf("thread id=%lu\n", pthread_self());
    return arg;
}

int demo_self_main(void)
{
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    printf("process id=%d\n", pid);

    pthread_create(&tid, NULL, thread_func_3_1, NULL);
    printf("pthread id=%lu\n", tid);
    pthread_join(tid, NULL);
    return 0;
}
