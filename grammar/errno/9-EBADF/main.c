#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd;
	int ret;
	fd = open("file.txt", O_RDWR | O_CREAT, 0644);

	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}

	// write to file
	char *str = "Hello, World!";
	write(fd, str, strlen(str));

	// close file
	close(fd);

	ret = write(fd, str, strlen(str));
	if (ret == -1) {
		perror("write");
		fprintf(stderr, "Error writing to file, errno = %d\n", errno);
		return EXIT_FAILURE;
	}
	// EBADF
	return EXIT_SUCCESS;
}

// output:
//
// ❯ xmake run errno_9_main
// write: Bad file descriptor
// Error writing to file, errno = 9
