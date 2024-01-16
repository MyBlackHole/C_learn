#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <unistd.h>

int demo_setsid_main(int argc, char **argv)
{
    pid_t gpid;
    pid_t old_gpid;
    if (fork() > 0)
    {
        printf("parent begin\n");
        // for (size_t i = 0; i < 30; i++)
        // {
        //     sleep(1);
        //     printf("parent count:%ld pid:%d\n", i, getpid());
        // }

        printf("parent exit\n");
        exit(0);
    }
    old_gpid = getpgrp();
    /* 脱离父进程组 */
    gpid = setsid();
    printf("ppid %d, gpid %d---%d\n", getppid(), old_gpid, gpid);

    printf("child begin\n");

    for (size_t i = 0; i < 10; i++)
    {
        sleep(1);
        printf("child count:%ld pid:%d\n", i, getpid());
    }

    printf("child exit\n");
    return 0;
}
