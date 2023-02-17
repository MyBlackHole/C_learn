#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void handler(int s)
{
    printf("触发了\n");
    sigset_t bset;
    sigemptyset(&bset);
    for (int i = 0; i < _SIGSET_NWORDS; i++)
    {
        printf("%ld\n", bset.__val[i]);
    }
    exit(0);
}

int main()
{
    /* signal(SIGFPE, SIG_IGN); */
    signal(SIGFPE, handler);
    int i = 0;
    i = i / 0;
    printf("正常结束了");
}
