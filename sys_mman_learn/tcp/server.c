#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAXLINE 4096

int main(int argc, char **argv)
{
	int ret;
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	int sendlen;
	int port = 0;

	if (argc != 2) {
		printf("usage: ./server <port>\n");
		return EXIT_FAILURE;
	}

	port = atoi(argv[1]);

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0) {
		printf("create socket error: %s(errno: %d)\n", strerror(errno),
		       errno);
		return listenfd;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	ret = bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if (ret == -1) {
		printf("bind socket error: %s(errno: %d)\n", strerror(errno),
		       errno);
		goto err_out;
	}

	ret = listen(listenfd, 10);
	if (ret < 0) {
		printf("listen socket error: %s(errno: %d)\n", strerror(errno),
		       errno);
		goto err_out;
	}

	printf("======waiting for client's request======\n");

	while (true) {
		connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);
		if (connfd == -1) {
			printf("accept socket error: %s(errno: %d)",
			       strerror(errno), errno);
			goto err_out;
		}

		while (true) {
			sendlen = send(connfd, buff, MAXLINE, 0);
			if (sendlen < 0) {
				printf("send socket error: %s(errno: %d)\n",
				       strerror(errno), errno);
				close(connfd);
				break;
			}
			if (sendlen == 0) {
				printf("client closed\n");
				close(connfd);
				break;
			}
			printf("send %d bytes to client\n", sendlen);
		}
		close(connfd);
	}
err_out:
	close(listenfd);
	return ret;
}
