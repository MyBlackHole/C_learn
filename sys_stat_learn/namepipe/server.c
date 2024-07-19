#include "unp.h"

int main()
{
	int res;
	int write_fd;
	int read_fd;
	ssize_t ret;

	char sendbuff[MAXLINE];
	char recvbuff[MAXLINE];

	if (access(read_fifo, F_OK) < 0) {
		// 检测是否存在
		// 创建写fifo，0755为执行权限
		res = mkfifo(write_fifo, ACCESSPERMS);
		if (res < 0) {
			ERR_EXIT("mkfifo err.");
		}
	}

	write_fd = open(write_fifo, O_WRONLY);
	if (write_fd < 0) {
		unlink(write_fifo); // 如果失败，删除
		ERR_EXIT("open write_fifo err.");
	}

	while ((read_fd = open(read_fifo, O_RDONLY)) < 0) {
		// 等待客户端创建读fifo
		sleep(1);
	}
	printf("client connect.\n");

	for (;;) {
		printf("client:>");
		ret = read(read_fd, recvbuff, MAXLINE);
		if (ret < 0) {
			ERR_EXIT("read err.");
		}
		printf("%s\n", recvbuff);

		printf("server:>");
		scanf("%s", sendbuff);
		write(write_fd, sendbuff, strlen(sendbuff) + 1);
	}
	unlink(write_fifo);

	return 0;
}
