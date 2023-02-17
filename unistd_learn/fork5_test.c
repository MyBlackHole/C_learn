#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

pid_t pid;

static void sleepm(int i);

static void pppp(int i) { printf("pppp\n"); }

static void fpppp(int i)
{
    printf("fpppp\n");
    /* usleep(300); */
    kill(pid, SIGUSR1);
    /* kill(pid, SIGKILL); */
    /* wait(0); */
}

int main(void)
{
    if ((pid = fork()) < 0)
    {
        printf("fork error");
    }
    else if (pid == 0)
    {
        /* 父进程退出时触发信号给子进程 */
        /* prctl(PR_SET_PDEATHSIG, SIGALRM); */

        /* sigset_t sigs; */
        /*  */
        /* #<{(| 清空并初始化信号集 |)}># */
        /* sigemptyset(&sigs); */
        /* #<{(| 添加信号到信号集 |)}># */
        /* sigaddset(&sigs, SIGINT); */
        /* #<{(| 屏蔽SIGINT信号 |)}># */
        /* sigprocmask(SIG_BLOCK, &sigs, 0); */
        printf("child pid:%d\n", getpid());
        printf("child pid:%d\n", getppid());
        kill(getppid(), SIGUSR1);

        signal(SIGUSR1, pppp);
        system("sleep 10");
        /* sleepm(0); */
        printf("output from child\n");
    }
    else
    {
        printf("output from parent\n");
        printf("parent pid:%d, child pid:%d\n", getpid(), pid);

        signal(SIGUSR1, fpppp);
        waitpid(pid, NULL, 0);
    }

    return 0;
}

static void sleepm(int i)
{
    time_t t = time((time_t*)NULL);
    printf("start time: %lu\n", t);
    for (; time((time_t*)NULL) < t + 10;)
        ;
}
