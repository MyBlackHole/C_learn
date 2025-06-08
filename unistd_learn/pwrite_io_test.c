#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE 8 * 1024

int demo_pwrite_io_main(int argc, char *argv[])
{
	int fd = 0;
	int nwrite;
	size_t offset = 0;

	char buf[BUFFSIZE] = { 0 };

	if (argc < 2) {
		printf("Usage: %s filename\n", argv[0]);
		return EXIT_FAILURE;
	}

	fd = open(argv[1], O_RDWR | O_CREAT, 0644);
	if (fd < 0) {
		perror("open failed");
		return EXIT_FAILURE;
	}
	/*nwrite = pwrite(fd, buf, BUFFSIZE, offset);*/
	/*if (nwrite != BUFFSIZE) {*/
	/*	perror("pwrite failed");*/
	/*	return EXIT_FAILURE;*/
	/*}*/
	/**/
	/*offset += nwrite;*/
	/**/
	/*nwrite = pwrite(fd, buf, BUFFSIZE, offset);*/
	/*if (nwrite != BUFFSIZE) {*/
	/*	perror("pwrite failed");*/
	/*	return EXIT_FAILURE;*/
	/*}*/

	offset = 0;
	nwrite = pwrite(fd, buf, BUFFSIZE, offset);
	if (nwrite != BUFFSIZE) {
		perror("pwrite failed");
		return EXIT_FAILURE;
	}
	/*关闭文件*/
	close(fd);

	return EXIT_SUCCESS;
}
