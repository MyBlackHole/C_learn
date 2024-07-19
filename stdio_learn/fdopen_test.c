#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int demo_fdopen_main(int argc, char *argv[])
{
	int fd_tmp = -1;
	FILE *file = NULL;
	fd_tmp = open("BUILD.gn", O_RDONLY);
	if (fd_tmp < 0) {
		perror(strerror(errno));
		exit(1);
	}
	file = fdopen(fd_tmp, "rb");
	fclose(file);
	close(fd_tmp);
	printf("%d\n", fd_tmp);
	exit(0);
}
