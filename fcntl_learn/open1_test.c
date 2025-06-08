#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int demo_open1_main(int argc, char *argv[])
{
	int fd_tmp = -1;
	fd_tmp = open("2.txt", O_RDWR | O_CREAT, 0744);
	if (fd_tmp <= 0) {
		perror("open()");
		exit(1);
	}

	puts("OK");

	close(fd_tmp);
	exit(EXIT_SUCCESS);
}
