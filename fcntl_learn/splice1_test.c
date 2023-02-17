#define _GNU_SOURCE
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: %s <file>\n", argv[0]);
        return 1;
    }
    int ret = 0;
    int filefd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
    assert(filefd > 0);

    // printf("errno:%s\n", strerror(errno));
    // 使用splice时， fd_in和fd_out中必须至少有一个是管道文件描述符。
    ret = splice(STDIN_FILENO, NULL, filefd, NULL, 32768, 0);
    printf("errno:%s\n", strerror(errno));
    assert(ret != -1);

    printf("errno:%d\n", errno);

    assert(ret != -1);

    close(filefd);
    return 0;
}
