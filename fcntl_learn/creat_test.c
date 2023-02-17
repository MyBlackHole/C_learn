#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char buf1[] = "qwertyuiop";
char buf2[] = "QWERTYUIOP";
int main(void)
{
    int fd;
    if ((fd = creat("myfile.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    {
        perror("creat error");
        exit(1);
    }
    if (write(fd, buf1, 10) != 10)
    {
        perror("write error");
    }
    if (lseek(fd, 16384, SEEK_SET) == -1)
    {
        perror("lseek error");
    }
    if (write(fd, buf2, 10) != 10)
    {
        perror("write error");
    }
    // 创建一个空洞文件，空洞文件是多线程的支持点之一，因为空洞文件的存在才能支持多线程断点续传

    exit(0);
}
