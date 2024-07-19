#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int demo_open_shm_main()
{
	const char *name = "/dev/shm/my_shared_memory";
	const char *buffer = "hello, world!\n";
	mode_t mode = DEFFILEMODE;
	int my_fd;
	size_t ret;

	my_fd = open(name, O_CREAT | O_RDWR | O_NOFOLLOW | O_CLOEXEC, mode);
	if (my_fd == -1) {
		perror("shm_open");
		exit(1);
	}

	ret = write(my_fd, buffer, strlen(buffer) + 1);
	if (ret < 0 || ret != (strlen(buffer) + 1)) {
		perror("write failed");
		exit(1);
	}

	close(my_fd);
	return 0;
}
