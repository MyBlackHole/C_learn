#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int demo_open_4_main(int argc, char *argv[])
{
	int fd_tmp = -1;
	int count = 10;

	while (count--) {
		fd_tmp = open("2.txt", O_RDWR | O_CREAT, 0744);
		if (fd_tmp <= 0) {
			perror("open()");
			exit(1);
		}

		printf("fd_tmp = %d\n", fd_tmp);

		close(fd_tmp);
	}
	exit(EXIT_SUCCESS);
}
