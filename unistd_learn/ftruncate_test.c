#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

uint64_t file_size = 10 * 1024 * 1024 * 1024ULL;

// 使用lseek、ftruncate到一个固定位置生成的“空洞文件”是不会占据真正的磁盘空间的
// 使用fallocate 或者posix_fallocate函数 真磁盘预分配
int main()
{
    int fd = -1;

    fd = open("fruncate.txt", O_RDWR | O_CREAT, 0666);
    if (fd < 0)
    {
        printf("open failed\n");
        return -1;
    }

    if (ftruncate(fd, file_size))
    {
        printf("ftruncate error\n");
        return -1;
    }

    // 移动位置
    lseek(fd, file_size - 1, SEEK_CUR);
    write(fd, "1", 1);

    close(fd);
    return 0;
}
