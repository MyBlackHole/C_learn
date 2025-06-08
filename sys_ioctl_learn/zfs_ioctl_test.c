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
#define STATUS 0

#define FS_IOC_READONLY _IOW('f', 3, long)

#define FS_APPEND_FL 0x00000020 /* writes to file may only append */
#define FS_READONLY 0x00100000 /* read only */
#define FS_FL_USER_MODIFIABLE 0x000380FF /* User modifiable flags */
// 100000000000000000000
// 000111000000011111111
int demo_zfs_ioctl_test_main(int argc, char *argv[])
{
	int fd_test;
	uint32_t flags = FS_APPEND_FL;
	int ret;

	if (argc < 2) {
		printf("Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// fd_test = open("/tmp/nfstest", O_RDONLY);
	// fd_test = open("/zfs_test/1.txt", O_RDONLY);
	fd_test = open(argv[1], O_RDONLY);
	if (fd_test < 0) {
		printf("open error %d\n", errno);
		exit(EXIT_FAILURE);
	}

	ret = ioctl(fd_test, FS_IOC_READONLY, &flags);
	if (ret < 0) {
		printf("ioctl error %d\n", errno);
		exit(EXIT_FAILURE);
	}

	printf("ioctl set FS_IOC_READONLY success\n");

	return EXIT_SUCCESS;
}
