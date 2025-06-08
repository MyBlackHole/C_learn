#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int demo_open_6_main(int argc, char *argv[])
{
	int ret = EXIT_SUCCESS;
	const int flags = O_RDWR | O_SYNC | O_DIRECT | O_CREAT;
	int fd = -1;
	int page_size = getpagesize();
	char *buffer = NULL;

	printf("page_size = %d\n", page_size);

	buffer = (char *)malloc(page_size);
	if (buffer == NULL) {
		perror("malloc()");
		ret = EXIT_FAILURE;
		goto exit__;
	}
	fd = open("open_6.txt", flags, ALLPERMS);
	if (fd <= 0) {
		perror("open()");
		ret = EXIT_FAILURE;
		goto free_buffer;
	}

	memset(buffer, 'a', page_size);

	if (write(fd, buffer, page_size) != page_size) {
		perror("write()");
		ret = EXIT_FAILURE;
		goto close_fd;
	}
close_fd:
	close(fd);
free_buffer:
	free(buffer);
exit__:
	exit(ret);
}
