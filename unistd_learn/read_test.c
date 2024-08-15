#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 1024

int demo_read_main(int argc, char *argv[])
{
	int fd_src = 0;
	int fd_dest = 0;
	/*char buf[512];*/
	char buf[BUFSIZE];
	unsigned int len = 0;
	printf("demo_read_main()\n");

	if (argc < 3) {
		fprintf(stderr, "Usage: %s <src_file> <dest_file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	printf("Source file: %s\n", argv[1]);
	fd_src = open(argv[1], O_RDWR);
	if (fd_src < 0) {
		perror("open()");
		exit(EXIT_FAILURE);
	}

	printf("Destination file: %s\n", argv[2]);
	fd_dest = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_dest < 0) {
		close(fd_src);
		perror("open()");
		exit(EXIT_FAILURE);
	}

	printf("Copying data from %s to %s\n", argv[1], argv[2]);
	while (true) {
		len = read(fd_src, buf, BUFSIZE);
		if (len < 0) {
			perror("read()");
			close(fd_dest);
			close(fd_src);
			exit(EXIT_FAILURE);
		}
		if (len == 0) {
			printf("Reached end of %s\n", argv[1]);
			break;
		}
		printf("Read %d bytes from %s\n", len, argv[1]);
		write(fd_dest, buf, len);
	}

	close(fd_dest);
	close(fd_src);

	printf("demo_read_main() done.\n");
	exit(EXIT_SUCCESS);
}
