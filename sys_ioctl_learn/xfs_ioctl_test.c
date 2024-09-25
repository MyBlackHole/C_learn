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

#define FS_READONLY 0x00100000 /* read only */
#define FS_IOC_SETFLAGS_READONLY _IOW('f', 126, int)

int demo_xfs_ioctl_test_main(int argc, char *argv[])
{
	int fd_test;
	uint32_t flags = FS_READONLY;
	int ret;

	if (argc < 2) {
		printf("Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	fd_test = open(argv[1], O_RDONLY);
	if (fd_test < 0) {
		printf("open error %d\n", errno);
		exit(EXIT_FAILURE);
	}

	ret = ioctl(fd_test, FS_IOC_SETFLAGS_READONLY, &flags);
	if (ret < 0) {
		printf("ioctl error %d\n", errno);
		exit(EXIT_FAILURE);
	}

	printf("ioctl set FS_IOC_SETFLAGS_READONLY success\n");

	return EXIT_SUCCESS;
}
