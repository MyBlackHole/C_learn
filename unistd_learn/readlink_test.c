#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 128

int demo_readlink_main(int argc, char *argv[])
{
	int abs_fd;
	char *obj_file;
	obj_file = malloc(SIZE);
	char buf[SIZE] = { '\n' };
	if (argc != 2) {
		printf("please input the filename \n");
		return EXIT_SUCCESS;
	}
	abs_fd = open(argv[1], O_RDWR | O_CREAT, DEFFILEMODE);
	if (abs_fd < 0) {
		perror("open file error \n");
		return EXIT_FAILURE;
	}

	snprintf(buf, sizeof(buf), "/proc/self/fd/%d", abs_fd);

	if (readlink((const char *)buf, obj_file, SIZE) < 0) {
		perror("readlink() error \n");
		return EXIT_FAILURE;
	}

	printf("The absolute filepath is: \n %s \n", obj_file);

	return EXIT_SUCCESS;
}
