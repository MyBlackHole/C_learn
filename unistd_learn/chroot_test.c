#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int demo_chroot_main(int argc, char *argv[])
{
	int ret = 0;
	int fd;
	// set root directory
	ret = chroot("rootfs");
	if (ret != 0) {
		perror("chroot");
		return EXIT_FAILURE;
	}
	// change to `/`
	ret = chdir("/");
	if (ret != 0) {
		perror("chdir");
		return EXIT_FAILURE;
	}

	fd = open("/var/aio_trackup_dir/1.txt", O_RDONLY | O_CREAT);
	if (fd < 0) {
		perror("open");
		return EXIT_FAILURE;
	}

	close(fd);

	return EXIT_SUCCESS;
}
