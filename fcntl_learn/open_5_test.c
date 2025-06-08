#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int demo_open_5_main(int argc, char *argv[])
{
	int fd_1 = -1;
	int fd_2 = -1;
	int fd_3 = -1;
	char file1[] = "open_5_test_1.txt";
	char file2[] = "open_5_test_2.txt";
	char file3[] = "open_5_test_3.txt";
	char buf[1024] = { 0 };
	int fd_tmp = -1;
	int count = 10;
	int ret = 0;
	fd_1 = open(file1, O_RDWR | O_CREAT, 0744);
	if (fd_1 <= 0) {
		perror("open()");
		exit(EXIT_FAILURE);
	}
	dprintf(fd_1, "Hello, world!\n");
	close(fd_1);

	fd_2 = open(file2, O_RDWR | O_CREAT, 0744);
	if (fd_2 <= 0) {
		perror("open()");
		exit(EXIT_FAILURE);
	}
	dprintf(fd_2, "Hello, world!\n");
	close(fd_2);

	fd_3 = open(file3, O_RDWR | O_CREAT, 0744);
	if (fd_3 <= 0) {
		perror("open()");
		exit(EXIT_FAILURE);
	}
	dprintf(fd_3, "Hello, world!\n");
	close(fd_3);

	while (count--) {
		fd_tmp = open(file1, O_RDONLY, 0744);
		if (fd_tmp <= 0) {
			perror("open()");
			exit(1);
		}

		printf("fd_tmp = %d\n", fd_tmp);

		ret = read(fd_tmp, buf, sizeof(buf));
		if (ret <= 0) {
			perror("read()");
			exit(1);
		} else {
			printf("%s", buf);
		}

		fd_tmp = open(file2, O_RDONLY, 0744);
		if (fd_tmp <= 0) {
			perror("open()");
			exit(1);
		}
		printf("fd_tmp = %d\n", fd_tmp);

		ret = read(fd_tmp, buf, sizeof(buf));
		if (ret <= 0) {
			perror("read()");
			exit(1);
		} else {
			printf("%s", buf);
		}

		fd_tmp = open(file3, O_RDONLY, 0744);
		if (fd_tmp <= 0) {
			perror("open()");
			exit(1);
		}
		ret = read(fd_tmp, buf, sizeof(buf));
		if (ret <= 0) {
			perror("read()");
			exit(1);
		} else {
			printf("%s", buf);
		}

		printf("fd_tmp = %d\n", fd_tmp);
	}
	exit(EXIT_SUCCESS);
}
