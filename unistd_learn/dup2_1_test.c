#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int oldfd;
    int newfd;
    size_t len;
    char *buf = "This is a test!!!!\n";
    oldfd = open("mine.txt", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
    if (oldfd == -1)
    {
        printf("open error\n");
        exit(EXIT_FAILURE);
    }
    newfd = dup2(oldfd, fileno(stdout));
    if (newfd == -1)
    {
        printf("dup2 error\n");
        exit(EXIT_FAILURE);
    }
    printf("dup2的返回值：%d\n", newfd);
    len = strlen(buf);
    // 本应该写入到stdout的信息，但是标准输出已经重定向到目标文件中，故向标准输出写的数据将会写到目标文件中。
    if (write(fileno(stdout), buf, len) != len)
    {
        printf("write error!\n");
        exit(EXIT_FAILURE);
    }
    close(newfd);
    exit(EXIT_SUCCESS);
}
