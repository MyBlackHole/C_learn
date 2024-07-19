#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define FNAME "/tmp/out"

int demo_dup_main(int argc, char *argv[])
{
	int fd_in = 0;
	int dfd = 0;
	int status = 0;
	fd_in = open(FNAME, O_WRONLY | O_CREAT | O_TRUNC, DEFFILEMODE);
	if (fd_in < 0) {
		perror("open()");
		exit(EXIT_FAILURE);
	}

	status = close(1);
	if (status < 0) {
		perror("close()");
		exit(EXIT_FAILURE);
	}

	dfd = dup(fd_in);
	if (dfd < 0) {
		perror("dup()");
		exit(EXIT_FAILURE);
	}
	close(fd_in);
	puts("black");
	exit(EXIT_SUCCESS);
}
