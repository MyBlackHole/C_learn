#include <aio.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 1025

int demo_aio_write_main(int argc, char **argv)
{
	// 定义aio控制块结构体
	struct aiocb wr_cb;

	int ret;
	int fd_tmp;

	char str[20] = { "hello,world" };

	// 置零wr结构体
	/* bzero(&wr, sizeof(wr)); */
	memset(&wr_cb, 0, sizeof(wr_cb));

	// 追加写
	fd_tmp = open("test.txt", O_WRONLY | O_APPEND);
	if (fd_tmp < 0) {
		perror("test.txt");
	}

	// 为aio.buf申请空间
	wr_cb.aio_buf = (char *)malloc(BUFFER_SIZE);
	if (wr_cb.aio_buf == NULL) {
		perror("buf");
	}

	wr_cb.aio_buf = str;

	// 填充aiocb结构
	wr_cb.aio_fildes = fd_tmp;
	wr_cb.aio_nbytes = 1024;

	// 异步写操作
	ret = aio_write(&wr_cb);
	if (ret < 0) {
		perror("aio_write");
	}

	// 等待异步写完成
	while (aio_error(&wr_cb) == EINPROGRESS) {
		printf("hello,world\n");
	}

	// 获得异步写的返回值
	ret = aio_return(&wr_cb);
	printf("\n\n\n返回值为:%d\n", ret);

	return 0;
}
