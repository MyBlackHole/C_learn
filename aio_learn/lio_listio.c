#include <aio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 1025

#define MAX_LIST 2

int demo_lio_listio_main(int argc, char **argv)
{
	struct aiocb *listio[2];
	struct aiocb rd_cb;
	struct aiocb wr_cb;
	int fd_tmp;
	int ret;

	// 异步读事件
	fd_tmp = open("test1.txt", O_RDONLY);
	if (fd_tmp < 0) {
		perror("test1.txt");
	}

	/* bzero(&rd, sizeof(rd)); */
	memset(&rd_cb, 0, sizeof(rd_cb));

	rd_cb.aio_buf = (char *)malloc(BUFFER_SIZE);
	if (rd_cb.aio_buf == NULL) {
		perror("aio_buf");
	}

	rd_cb.aio_fildes = fd_tmp;
	rd_cb.aio_nbytes = 1024;
	rd_cb.aio_offset = 0;
	rd_cb.aio_lio_opcode = LIO_READ; /// lio操作类型为异步读

	// 将异步读事件添加到list中
	listio[0] = &rd_cb;

	// 异步些事件
	fd_tmp = open("test2.txt", O_WRONLY | O_APPEND);
	if (fd_tmp < 0) {
		perror("test2.txt");
	}

	/* bzero(&wr, sizeof(wr)); */
	memset(&wr_cb, 0, sizeof(wr_cb));

	wr_cb.aio_buf = (char *)malloc(BUFFER_SIZE);
	if (wr_cb.aio_buf == NULL) {
		perror("aio_buf");
	}

	wr_cb.aio_fildes = fd_tmp;
	wr_cb.aio_nbytes = 1024;

	wr_cb.aio_lio_opcode = LIO_WRITE; /// lio操作类型为异步写

	// 将异步写事件添加到list中
	listio[1] = &wr_cb;

	// 使用lio_listio发起一系列请求
	ret = lio_listio(LIO_WAIT, listio, MAX_LIST, NULL);

	// 当异步读写都完成时获取他们的返回值

	ret = aio_return(&rd_cb);
	printf("\n读返回值:%d", ret);

	ret = aio_return(&wr_cb);
	printf("\n写返回值:%d", ret);

	return 0;
}
