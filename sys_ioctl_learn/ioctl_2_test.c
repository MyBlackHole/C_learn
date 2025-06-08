#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <linux/limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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
	FSBACKUP_IIOCTL_GET_MOD_MONITOR_STATUS,
};

int demo_ioctl_2_test_main(int argc, char *argv[])
{
	int fd_test;
	int ret;
	char path[PATH_MAX] = { 0 };

	if (argc < 3) {
		printf("Usage: %s <dev> <path>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	memcpy(path, argv[2], strlen(argv[2]));

	fd_test = open(argv[1], O_RDONLY);
	if (fd_test < 0) {
		printf("open error %d\n", errno);
		exit(EXIT_FAILURE);
	}

	ret = ioctl(fd_test, FSBACKUP_IIOCTL_GET_MOD_MONITOR_STATUS, path);
	if (ret) {
		printf("ioctl error %d\n", errno);
		exit(EXIT_FAILURE);
	}
	if (*(int *)path == 1) {
		printf("module is monitoring\n");
	} else {
		printf("module is not monitoring\n");
	}

	printf("ioctl success\n");

	return EXIT_SUCCESS;
}
