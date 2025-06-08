#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

// 根据文件描述词来操作文件的特性
int demo_fcntl_main(int argc, char **argv)
{
	int val;
	if (argc != 2) {
		fprintf(stderr, "usage:%s <descriptor#>", argv[0]);
		exit(1);
	}
	val = fcntl(atoi(argv[1]), F_GETFL, 0);
	if (val < 0) {
		fprintf(stderr, "fcntl error for fd %d", atoi(argv[1]));
		exit(1);
	}
	switch (val & O_ACCMODE) {
	case O_RDONLY:
		printf("read only");
		break;
	case O_WRONLY:
		printf("write only");
		break;
	case O_RDWR:
		printf("read write");
		break;
	default:
		perror("unknow access mode");
		exit(1);
	}
	if (val & O_APPEND) {
		printf(",append");
	}
	if (val & O_NONBLOCK) {
		printf("，nonblocking");
	}
	if (val & O_SYNC) {
		printf(",synchronous writes");
	}
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
	if (val & O_FSYNC)
		printf(",synchoronous writes");
#endif
	putchar('\n');
	exit(0);
}
