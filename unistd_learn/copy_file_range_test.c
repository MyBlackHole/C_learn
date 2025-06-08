#define _FILE_OFFSET_BITS 64
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

// 将一系列数据从一个文件复制到另一个文件
int demo_copy_file_range_main(int argc, char *argv[])
{
	int fd_in;
	int fd_out;
	off_t len;
	off_t ret;
	struct stat stat;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1) {
		perror("open (argv[1])");
		exit(EXIT_FAILURE);
	}

	if (fstat(fd_in, &stat) == -1) {
		perror("fstat");
		exit(EXIT_FAILURE);
	}

	len = stat.st_size;

	fd_out = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, DEFFILEMODE);
	if (fd_out == -1) {
		perror("open (argv[2])");
		exit(EXIT_FAILURE);
	}

	do {
		ret = copy_file_range(fd_in, NULL, fd_out, NULL, len, 0);
		if (ret == -1) {
			perror("copy_file_range");
			exit(EXIT_FAILURE);
		}

		len -= ret;
	} while (len > 0 && ret > 0);

	close(fd_in);
	close(fd_out);
	exit(EXIT_SUCCESS);
}
