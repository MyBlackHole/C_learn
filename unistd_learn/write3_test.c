#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024 * 8

int demo_write3_main(int argc, char *argv[])
{
	int ret = EXIT_SUCCESS;
	int fd = 0;
	char *filename;

	if (argc < 3) {
		printf("Usage: %s filename write_count\n", argv[0]);
		return EXIT_FAILURE;
	}

	filename = argv[1];
	fd = open(filename, O_WRONLY | O_APPEND, 0644);
	if (fd < 0) {
		perror("open");
		ret = -errno;
		goto exit;
	}
	int n = write(fd, argv[2], strlen(argv[2]));
	if (n < 0) {
		perror("write");
		ret = -errno;
		goto close_fd;
	}
	printf("%d bytes written to %s\n", n, filename);
close_fd:
	close(fd);
exit:
	return ret;
}
