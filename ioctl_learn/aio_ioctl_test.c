#include <errno.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

enum {
	FSBACKUP_IIOCTL_READ_COUNT = 100000,
	FSBACKUP_IIOCTL_INCR_COUNT,
	FSBACKUP_IIOCTL_READ_PIDS,
	FSBACKUP_IIOCTL_SET_BACKUP_PATH,
	FSBACKUP_IIOCTL_DEL_BACKUP_PATH,
	FSBACKUP_IIOCTL_SET_EXCLUDE_PATH,
	FSBACKUP_IIOCTL_DEL_EXCLUDE_PATH,
	FSBACKUP_IIOCTL_GET_MOD_ERR_INFO,
};

typedef struct IODataPath {
	char path[256];
} io_data_path;

int demo_aio_ioctl_test_main(int argc, char *argv[])
{
	int fd_test;
	io_data_path data_path = { 0 };
	int ret;

	if (argc < 3) {
		printf("Usage: %s <dev> <path>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	fd_test = open(argv[1], O_RDONLY);
	if (fd_test < 0) {
		printf("open error %d\n", errno);
		exit(EXIT_FAILURE);
	}

	memcpy(data_path.path, argv[2], strlen(argv[2]));

	ret = ioctl(fd_test, FSBACKUP_IIOCTL_SET_EXCLUDE_PATH, &data_path);
	if (ret) {
		printf("ioctl error %d\n", errno);
		exit(EXIT_FAILURE);
	}

	printf("ioctl set success\n");

	return EXIT_SUCCESS;
}
