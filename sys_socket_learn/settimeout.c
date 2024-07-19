#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#define SERVER_PORT 8008
#define MESSAGE "HTTP/1.1 200 OK\r\nContent-Length: 11\r\n\r\nhello world"

int demo_SO_RCVTIMEO_main()
{
	struct sockaddr_in srvaddr;
	struct timeval timeout = { 10, 0 };
	int locfd;
	int sockopt = 1;
	int res;

	/*创建一个套接字*/
	locfd = socket(AF_INET, SOCK_STREAM, 0);
	if (locfd < 0) {
		printf("create socket error!\n");
		return -1;
	}

	printf("socket ready!\n");

	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(SERVER_PORT);
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// // close 的话会导致套接字异常
	// // Bad file descriptor: Bad file descriptor
	// close(locfd);
	// printf("close socket\n");

	// 设置端口重用
	res = setsockopt(locfd, SOL_SOCKET, SO_REUSEADDR, &sockopt,
			 sizeof(int));
	if (res < 0) {
		perror(strerror(errno));
		return -1;
	}

	/*bind, 将网络地址与端口绑定*/
	res = bind(locfd, (struct sockaddr *)&srvaddr, sizeof(srvaddr));
	if (res < 0) {
		printf("bind error!\n");
		close(locfd);
		return -1;
	}

	printf("bind ready!\n");

	/*listen, 监听端口*/
	listen(locfd, 10);

	printf("等待来自客户端的连接......\n");

	while (1) {
		struct sockaddr_in cliaddr;
		socklen_t len = sizeof(cliaddr);
		int clifd;

		timeout.tv_sec = 0;

		if (setsockopt(locfd, SOL_SOCKET, SO_RCVTIMEO, &timeout,
			       sizeof(struct timeval)) == -1) {
			printf("set setsockopt recv time out error!\n");
			close(locfd);
			return -1;
		}

		/*bind, 将网络地址与端口绑定*/
		clifd = accept(locfd, (struct sockaddr *)&cliaddr, &len);
		if (clifd < 0) {
			printf("accept error! %s\n", strerror(errno));
			close(locfd);
			return -1;
		}

		/*输出客户机的信息*/
		char *ip = inet_ntoa(cliaddr.sin_addr);

		printf("客户机: %s连接到本服务器成功!\n", ip);

		timeout.tv_sec = 10;

		// 设置 发送 超时
		if (setsockopt(clifd, SOL_SOCKET, SO_SNDTIMEO, &timeout,
			       sizeof(struct timeval)) == -1) {
			printf("set setsockopt send time out error!\n");
			close(locfd);
			return -1;
		}

		// 设置 读取 超时
		if (setsockopt(clifd, SOL_SOCKET, SO_RCVTIMEO, &timeout,
			       sizeof(struct timeval)) == -1) {
			printf("set setsockopt recv time out error!\n");
			close(locfd);
			return -1;
		}

		/*输出客户机请求的信息*/
		char buff[1024] = { 0 };
		int size = read(clifd, buff, sizeof(buff));

		printf("Request information: ");

		printf("%s\n", buff);

		printf("%d bytes\n", size);

		write(clifd, MESSAGE, strlen(MESSAGE));

		close(clifd);
	}

	close(locfd);

	return 0;
}
