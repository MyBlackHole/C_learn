/*socketpair1.c*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd[2];
    int r = socketpair(AF_UNIX, SOCK_STREAM, 0, fd);
    if (r < 0)
    {
        perror("socketpair()");
        exit(1);
    }

    if (fork())
    { /* 父进程 */
        int val = 0;
        close(fd[1]);
        while (1)
        {
            sleep(1);
            ++val;
            printf("发送数据: %d\n", val);
            write(fd[0], &val, sizeof(val));
            read(fd[0], &val, sizeof(val));
            printf("接收数据: %d\n", val);
        }
    }
    else
    { /*子进程*/
        int val;
        close(fd[0]);
        while (1)
        {
            read(fd[1], &val, sizeof(val));
            ++val;
            write(fd[1], &val, sizeof(val));
        }
    }
}
