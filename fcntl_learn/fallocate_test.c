#define _GNU_SOURCE /* See feature_test_macros(7) */
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

uint64_t file_size = 10 * 1024 * 1024 * 1024ULL;

// int fallocate(int fd, int mode, off_t offset, off_t len);
// int posix_fallocate(int fd, off_t offset, off_t len);

// 使用fallocate 或者posix_fallocate函数 真磁盘预分配
int main()
{
    int fd = -1;
    int ret = -1;

    fd = open("tmp.txt", O_CREAT | O_RDWR, 0666);
    if (fd < 0)
    {
        printf("fd < 0");
        return -1;
    }

    // ret = fallocate(fd, 0, 0, file_size);
    ret = posix_fallocate(fd, 0, file_size);
    if (ret < 0)
    {
        printf("ret = %d, errno = %d,  %s\n", ret, errno, strerror(errno));
        return -1;
    }

    printf("fallocate create %.2fG file\n", file_size / 1024 / 1024 / 1024.0);

    close(fd);

    return 0;
}
