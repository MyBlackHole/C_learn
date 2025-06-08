#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int demo_lseek1_main(int argc, char *argv[])
{
	int fd_i = 0;
	int num = 10;
	char *str = malloc(num);

	if (argc < 2) {
		fprintf(stderr, "<path>\n");
		exit(1);
	}

	fd_i = open(argv[1], O_RDONLY);
	lseek(fd_i, 1, SEEK_SET);

	// write(fd, "ok", 3);
	read(fd_i, str, num);
	printf("%s\n", str);

	close(fd_i);

	exit(0);
}
