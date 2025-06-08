#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int demo_open_3_main(int argc, char *argv[])
{
	int fd_tmp = -1;
	fd_tmp = open("append_test.txt", O_RDWR | O_CREAT | O_APPEND, 0744);
	if (fd_tmp <= 0) {
		perror("open()");
		exit(EXIT_FAILURE);
	}

	write(fd_tmp, "aaaaaaaaaaaaa", 13);

	close(fd_tmp);
	exit(EXIT_SUCCESS);
}
