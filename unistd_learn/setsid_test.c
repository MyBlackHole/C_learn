#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (fork() > 0)
    {
        printf("parent begin\n");
        sleep(10);

        printf("parent exit\n");
        exit(0);
    }

    /* 脱离父进程组 */
    setsid();

    printf("child begin\n");
    sleep(100);

    printf("child exit\n");
    return 0;
}
