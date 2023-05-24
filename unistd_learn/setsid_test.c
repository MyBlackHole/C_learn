#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (fork() > 0)
    {
        printf("parent begin\n");
        for (size_t i = 0; i < 30; i++)
        {
            sleep(1);
            printf("parent count:%ld pid:%d\n", i, getpid());
        }

        printf("parent exit\n");
        exit(0);
    }

    /* 脱离父进程组 */
    setsid();

    printf("child begin\n");

    for (size_t i = 0; i < 100; i++)
    {
        sleep(1);
        printf("child count:%ld pid:%d\n", i, getpid());
    }

    printf("child exit\n");
    return 0;
}
