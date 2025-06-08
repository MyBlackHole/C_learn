#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define FILE_SIZE 10 * 1024

#define G_SIZE 10

// int fallocate(int fd, int mode, off_t offset, off_t len);
// int posix_fallocate(int fd, off_t offset, off_t len);

// 使用fallocate 或者posix_fallocate函数 真磁盘预分配
int demo_fallocate_main()
{
	int tmp_fd = -1;
	int ret = -1;

	tmp_fd = open("tmp.txt", O_CREAT | O_RDWR,
		      S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (tmp_fd < 0) {
		printf("fd < 0");
		return -1;
	}

	/*ftruncate(tmp_fd, 0);*/
	ret = fallocate(tmp_fd, FALLOC_FL_ZERO_RANGE, 0, (off_t)FILE_SIZE);
	/*ret = fallocate(tmp_fd, 0, 0, (off_t)FILE_SIZE);*/
	/*ret = posix_fallocate(tmp_fd, 0, (off_t)FILE_SIZE);*/
	if (ret < 0) {
		printf("ret = %d, errno = %d,  %s\n", ret, errno,
		       strerror(errno));
		return -1;
	}

	printf("fallocate create %ldG file\n", (off_t)G_SIZE);

	close(tmp_fd);

	return 0;
}
