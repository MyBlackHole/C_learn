#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define FIFO "stdout_fifo"

int main()
{
    int status;
    // 清除 FIFO
    unlink(FIFO);
    // 创建 FIFO
    int res = mkfifo(FIFO, 0777);
    if (res == -1)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // 分裂
    if (fork() == 0)
    {
        int fd = open(FIFO, O_WRONLY);

        // 重定向 输出
        dup2(fd, 1);

        execl("/bin/ls", "-a", (char*)0);
    }
    else
    {
        char child_stdout[1024] = {0};
        int fd = open(FIFO, O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            exit(-1);
        }

        sleep(3);
        read(fd, child_stdout, sizeof(child_stdout));
        printf("Parent: %s", child_stdout);
        printf("Finished!\n");

        wait(&status);
        printf("child:%d\n", status);
    }
    return EXIT_SUCCESS;
}
