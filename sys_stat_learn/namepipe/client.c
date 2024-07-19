#include "unp.h"

int main()
{
	int res;
	int read_fd;
	int write_fd;
	char sendbuff[MAXLINE];
	char recvbuff[MAXLINE];

	ssize_t ret;

	res = mkfifo(read_fifo, ACCESSPERMS);

	if (res < 0) {
		ERR_EXIT("mkfifo err.");
	}
	read_fd = open(write_fifo, O_RDONLY);
	if (read_fd < 0) {
		ERR_EXIT("open err.");
	}
	write_fd = open(read_fifo, O_WRONLY);
	if (write_fd < 0) {
		unlink(read_fifo);
		ERR_EXIT("open write_fifo err.");
	}

	for (;;) {
		printf("client:>");
		scanf("%s", sendbuff);
		ret = write(write_fd, sendbuff, strlen(sendbuff) + 1);
		if (ret < 0) {
			ERR_EXIT("write err.");
		}

		printf("server:>");
		read(read_fd, recvbuff, MAXLINE);
		printf("%s\n", recvbuff);
	}

	unlink(read_fifo);

	return 0;
}
