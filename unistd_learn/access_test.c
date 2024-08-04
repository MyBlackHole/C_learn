#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int demo_access_main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "usage:%s <pathname>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (access(argv[1], F_OK) < 0) {
		// 小于 0 代表不存在
		fprintf(stderr, "access error for %s\n", argv[1]);
		perror("F_OK access error");
		exit(EXIT_FAILURE);
	} else {
		perror("F_OK access OK");
		printf("tread access OK\n");
	}

	if (access(argv[1], R_OK) < 0) {
		// 小于 0 代表不存在
		fprintf(stderr, "access error for %s\n", argv[1]);
		perror("R_OK access error");
		exit(EXIT_FAILURE);
	} else {
		perror("R_OK access OK");
		printf("read access OK\n");
	}

	if (open(argv[1], O_RDONLY) < 0) {
		fprintf(stderr, "\topen error for %s\n", argv[1]);
		exit(EXIT_FAILURE);
	} else {
		printf("open for reading OK \n");
	}
	exit(EXIT_SUCCESS);
}
