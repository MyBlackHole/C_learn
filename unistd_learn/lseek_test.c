#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

int demo_lseek_main(int argc, char *argv[])
{
	int fd_i = 0;
	if (argc < 2) {
		fprintf(stderr, "<path>\n");
		exit(1);
	}

	fd_i = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, DEFFILEMODE);
	lseek(fd_i, 5LL * 1024LL * 1024LL * 1024LL - 1LL, SEEK_SET);

	write(fd_i, "", 1);

	close(fd_i);

	exit(EXIT_SUCCESS);
}
