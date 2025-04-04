#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024 * 8

int demo_write2_main(int argc, char *argv[])
{
	int fd = 0;
	int count = 0;
	char *filename;
	char buffer[BUFFER_SIZE] = { 'a' };

	if (argc < 3) {
		printf("Usage: %s filename write_count\n", argv[0]);
		return EXIT_FAILURE;
	}

	filename = argv[1];
	count = atoi(argv[2]);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0) {
		perror("open");
		return EXIT_FAILURE;
	}
	while (count > 0) {
		int n = write(fd, buffer, BUFFER_SIZE);
		if (n < 0) {
			perror("write");
			return EXIT_FAILURE;
		}
		if (n == 0) {
			printf("write returned 0, file size is %ld\n",
			       lseek(fd, 0, SEEK_END));
			return EXIT_FAILURE;
		}
		if (n < BUFFER_SIZE) {
			printf("write returned %d, file size is %ld\n", n,
			       lseek(fd, 0, SEEK_END));
			return EXIT_FAILURE;
		}
		count--;
	}
	return EXIT_SUCCESS;
}
