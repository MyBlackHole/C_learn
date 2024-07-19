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

#define BUFFER_SIZE 1024

#define MAX_LIST 2

int demo_aio_suspend_main(int argc, char **argv)
{
	// aio操作所需结构体
	struct aiocb rd_cb;

	int fd_tmp;
	int ret;
	int couter;

	// cblist链表
	struct aiocb const *aiocb_list[2];

	fd_tmp = open("test.txt", O_RDONLY);
	if (fd_tmp < 0) {
		perror("test.txt");
	}

	// 将rd结构体清空
	/* bzero(&rd, sizeof(rd)); */
	memset(&rd_cb, 0, sizeof(rd_cb));

	// 为rd.aio_buf分配空间
	rd_cb.aio_buf = malloc(BUFFER_SIZE + 1);

	// 填充rd结构体
	rd_cb.aio_fildes = fd_tmp;
	rd_cb.aio_nbytes = BUFFER_SIZE;
	rd_cb.aio_offset = 0;

	// 将读fd的事件注册
	aiocb_list[0] = &rd_cb;

	// 进行异步读操作
	ret = aio_read(&rd_cb);
	if (ret < 0) {
		perror("aio_read");
		exit(1);
	}

	couter = 0;
	//  循环等待异步读操作结束
	while (aio_error(&rd_cb) == EINPROGRESS) {
		printf("第%d次， %s\n", ++couter, (char *)rd_cb.aio_buf);
	}

	printf("我要开始等待异步读事件完成\n");
	// 阻塞等待异步读事件完成
	ret = aio_suspend(aiocb_list, MAX_LIST, NULL);

	// 获取异步读返回值
	ret = aio_return(&rd_cb);

	printf("\n\n返回值为:%d\n", ret);

	return 0;
}
