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
#define CMD_TEST_4 4

struct struct_regs {
	int data;
};

int demo_app_main(int argc, char *argv[])
{
	int fd_tmp = 0;
	int rev_data = 0;

	fd_tmp = open("/dev/test_ioctrl", O_RDWR);
	if (fd_tmp < 0) {
		printf("open failed\n");
		exit(EXIT_FAILURE);
	}
	printf("open success\n");

	/*依次调用四个命令*/
	ioctl(fd_tmp, CMD_TEST_0);

	rev_data = ioctl(fd_tmp, CMD_TEST_1);
	printf("receive 1 data=%d\n", rev_data);

	ioctl(fd_tmp, CMD_TEST_2, 99);

	rev_data = ioctl(fd_tmp, CMD_TEST_3, 101);
	printf("receive 3 data=%d\n", rev_data);

	struct struct_regs data = {};
	data.data = 100;
	printf("p=%p\n", &data);
	ioctl(fd_tmp, 4, &data);

	close(fd_tmp);
	return EXIT_SUCCESS;
}
