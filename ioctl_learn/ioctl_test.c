#include <errno.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM 30

int main(void)
{
    int fd_test;
    // off_t size
    int size;
    int len;
    int ret;

    fd_test = open("/dev/sda", O_RDONLY);
    if (fd_test < 0)
    {
        printf("open error %d\n", errno);
        exit(-1);
    }

#if 0
    //会报错
    if ((size = lseek(fd, 0, SEEK_END)) < 0)
    {
        printf("lseek errno %d\n", errno);
        exit(-1);
    }
#endif
    // 获取设备块大小 bytes
    ret = ioctl(fd_test, BLKGETSIZE64, &size);
    if (ret < 0)
    {
        printf("ioctl error %d\n", errno);
        exit(-1);
    }

    len = (size >> NUM);
    printf("size of sda = %d G\n", len);

    return 0;
}
