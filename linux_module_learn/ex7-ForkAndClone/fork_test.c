#define _GNU_SOURCE
#include <malloc.h>
#include <sched.h>  //clone()相关
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>  //fork()相关

int param = 0;

int thread_fn(void *data)
{
    int j;
    printf("starting child thread_fn, pid=%d\n", getpid());
    for (j = 0; j < 10; j++)
    {
        param = j + 1000;
        sleep(1);
        printf("child thread running: j=%d, param=%d secs\n", j, param);
    }
    printf("child thread_fn exit\n");
    return 0;
}

int main(int argc, char **argv)
{
    int j, tid, pagesize, stacksize;
    void *stack;

    printf("starting parent process, pid=%d\n", getpid());

    pagesize = getpagesize();
    stacksize = 4 * pagesize;

    posix_memalign(&stack, pagesize, stacksize);

    printf("Setting a clone child thread with stacksize = %d....", stacksize);
    tid = clone(thread_fn, (char *)stack + stacksize, CLONE_VM | SIGCHLD, 0);
    printf(" with tid=%d\n", tid);
    if (tid < 0)
        exit(EXIT_FAILURE);

    for (j = 0; j < 6; j++)
    {
        param = j;
        sleep(1);
        printf("parent running: j=%d, param=%d secs\n", j, param);
    }
    printf("parent killitself\n");
    exit(EXIT_SUCCESS);
}
