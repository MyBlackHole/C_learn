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

int main(void)
{
    int fd;
    // off_t size
    uint64_t size;
    int len;
    int r;

    if ((fd = open("/dev/sda", O_RDONLY)) < 0)
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
    if ((r = ioctl(fd, BLKGETSIZE64, &size)) < 0)
    {
        printf("ioctl error %d\n", errno);
        exit(-1);
    }

    len = (size >> 30);
    printf("size of sda = %d G\n", len);

    return 0;
}
