#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM 1024

#define FIFO "stdout_fifo"

int demo_mkfifo_main()
{
    int status;
    // 清除 FIFO
    unlink(FIFO);
    // 创建 FIFO
    int res = mkfifo(FIFO, ACCESSPERMS);
    if (res == -1)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // 分裂
    if (fork() == 0)
    {
        int o_fd = open(FIFO, O_WRONLY);

        // 重定向 输出
        dup2(o_fd, 1);

        execl("/bin/ls", "-a", (char *)0);
    }
    else
    {
        char child_stdout[NUM] = {0};
        int  o_fd              = open(FIFO, O_RDONLY);
        if (o_fd == -1)
        {
            perror("open");
            exit(-1);
        }

        sleep(3);
        read(o_fd, child_stdout, sizeof(child_stdout));
        printf("Parent: child_stdout \n[\n%s\n]\n", child_stdout);
        printf("Finished!\n");

        wait(&status);
        printf("child:%d\n", status);
    }
    return EXIT_SUCCESS;
}
