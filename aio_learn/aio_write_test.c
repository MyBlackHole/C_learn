#include <aio.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 1025

int main(int argc, char **argv)
{
    // 定义aio控制块结构体
    struct aiocb wr;

    int ret, fd;

    char str[20] = {"hello,world"};

    // 置零wr结构体
    /* bzero(&wr, sizeof(wr)); */
    memset(&wr, 0, sizeof(wr));

    // 追加写
    fd = open("test.txt", O_WRONLY | O_APPEND);
    if (fd < 0)
    {
        perror("test.txt");
    }

    // 为aio.buf申请空间
    wr.aio_buf = (char *)malloc(BUFFER_SIZE);
    if (wr.aio_buf == NULL)
    {
        perror("buf");
    }

    wr.aio_buf = str;

    // 填充aiocb结构
    wr.aio_fildes = fd;
    wr.aio_nbytes = 1024;

    // 异步写操作
    ret = aio_write(&wr);
    if (ret < 0)
    {
        perror("aio_write");
    }

    // 等待异步写完成
    while (aio_error(&wr) == EINPROGRESS)
    {
        printf("hello,world\n");
    }

    // 获得异步写的返回值
    ret = aio_return(&wr);
    printf("\n\n\n返回值为:%d\n", ret);

    return 0;
}
