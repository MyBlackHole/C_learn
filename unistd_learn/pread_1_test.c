#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFSIZE 1024 * 10

int demo_pread_1_main(void)
{
	char pathname[] = "/tmp/myfile";
	int fd = 0;
	ssize_t nread;
	char buf[BUFFSIZE];
	size_t nbytes;

	fd = open(pathname, O_RDWR | O_CREAT);
	if (fd < 0) {
		printf("open error for %s\n", pathname);
		return EXIT_FAILURE;
	}

	nbytes = 10;

	nread = pread(fd, buf, nbytes, 100);
	if (nread < 0) {
		fprintf(stderr, "read_len:%ld, failed.(%s),\n", nread,
			strerror(errno));
		return EXIT_FAILURE;
	}
	fprintf(stderr, "read_len:%ld, (%s),\n", nread, strerror(errno));

	close(fd);

	return EXIT_SUCCESS;
}

// Output:
//
// echo 22323 > /tmp/myfile
// ❯ xmake run unistd_learn pread_1
// read_len:6, (Success),
