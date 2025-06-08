#include <fcntl.h>
#include <libgen.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFSIZE 4096

struct point {
	int64_t a;
	int32_t b;
};

typedef struct point point_t;

int demo_wrs_main(int argc, char *argv[])
{
	size_t len;
	point_t point1;
	point_t point2;

	char *name = "/write_read_struct_test.bin";
	char *path = dirname(argv[0]);
	char *file_path = malloc(strlen(name) + strlen(path));
	strcpy(file_path, path);
	strcat(file_path, name);

	int fd_in;

	fd_in = open(file_path, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd_in < 0) {
		perror("open()");
		exit(EXIT_FAILURE);
	}

	// write test
	point2.a = 1000;
	point2.b = 1111;
	len = write(fd_in, &point2, sizeof(point2));
	if (len != sizeof(point2)) {
		perror("write error");
		exit(EXIT_FAILURE);
	}

	lseek(fd_in, 0, SEEK_SET);

	// read test
	len = read(fd_in, &point1, sizeof(point1));
	if (len != sizeof(point1)) {
		perror("read error");
		exit(EXIT_FAILURE);
	}

	printf("%d - %ld\n", point1.b, len);

	free(file_path);
	exit(EXIT_SUCCESS);
}
