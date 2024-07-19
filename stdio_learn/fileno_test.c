#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int demo_fileno_main(int argc, char *argv[])
{
	int fd_tmp = -1;
	FILE *file = NULL;
	file = fopen("BUILD.gn", "rb");
	if (file == NULL) {
		perror(strerror(errno));
		exit(1);
	}
	fd_tmp = fileno(file);
	close(fd_tmp);
	fclose(file);
	printf("%d\n", fd_tmp);
	exit(0);
}
