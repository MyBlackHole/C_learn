#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FILE_SIZE 10 * 1024 * 1024 * 1024ULL

// 使用lseek、ftruncate到一个固定位置生成的“空洞文件”是不会占据真正的磁盘空间的
// 使用fallocate 或者posix_fallocate函数 真磁盘预分配
int demo_ftruncate1_main()
{
	int fd_in = -1;

	fd_in = open("/home/black/1.txt", O_RDWR | O_CREAT, ALLPERMS);
	if (fd_in < 0) {
		printf("open failed\n");
		return EXIT_FAILURE;
	}

	if (ftruncate(fd_in, 0)) {
		printf("ftruncate error\n");
		return EXIT_FAILURE;
	}

	close(fd_in);
	return EXIT_SUCCESS;
}
