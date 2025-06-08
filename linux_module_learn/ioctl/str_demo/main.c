#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include "ioctl_test.h"

#define DEV_PATH "/dev/ioctl_test"

int main(int argc, const char *argv[])
{
	char buf[128] = { 0 };
	int fd = -1;
	image_t image;
	image.high = 200;
	image.width = 10;
	printf("%s", DEV_PATH);
	fd = open(DEV_PATH, O_RDWR);
	if (fd == -1) {
		perror("open is error\n");
		return -1;
	}
	ioctl(fd, UACCESS_STRUCT, &image);
	printf("用户空间: width=%d  high=%d\n", image.width, image.high);

	printf("please input>>>>>");
	fgets(buf, sizeof(buf), stdin);
	buf[strlen(buf) - 1] = 0;
	ioctl(fd, UACCESS_BUF, buf);

	close(fd);
	return 0;
}
