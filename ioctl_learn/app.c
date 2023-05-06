#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define CMD_TEST_0 _IO('A', 0)
#define CMD_TEST_1 _IOR('A', 1, int)
#define CMD_TEST_2 _IOW('A', 2, int)
#define CMD_TEST_3 _IOWR('A', 3, int)

int main(int argc, char *argv[])
{
    int fd = 0;
    int revData = 0;

    fd = open("/dev/test_ioctrl", O_RDWR);
    if (fd < 0)
    {
        printf("open failed\n");
        exit(1);
    }
    printf("open success\n");

    /*依次调用四个命令*/
    ioctl(fd, CMD_TEST_0);

    revData = ioctl(fd, CMD_TEST_1);
    printf("receive 1 data=%d\n", revData);

    ioctl(fd, CMD_TEST_2, 99);

    revData = ioctl(fd, CMD_TEST_3, 101);
    printf("receive 3 data=%d\n", revData);

    close(fd);
    return 0;
}
