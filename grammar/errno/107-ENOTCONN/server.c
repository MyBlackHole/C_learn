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
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	/*char buff[4096];*/
	/*int n;*/

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("create socket error: %s(errno: %d)\n", strerror(errno),
		       errno);
		return 0;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(6666);

	if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) ==
	    -1) {
		printf("bind socket error: %s(errno: %d)\n", strerror(errno),
		       errno);
		return 0;
	}

	if (listen(listenfd, 10) == -1) {
		printf("listen socket error: %s(errno: %d)\n", strerror(errno),
		       errno);
		return 0;
	}

	printf("====== start accept ======\n");
	while (1) {
		if ((connfd = accept(listenfd, (struct sockaddr *)NULL,
				     NULL)) == -1) {
			printf("accept socket error: %s(errno: %d)",
			       strerror(errno), errno);
			continue;
		}

		printf("accept: %d\n", connfd);

		for (int i = 0; i < 5; i++) {
			send(connfd, "hello", 6, 0);
			sleep(1);
		}
		shutdown(connfd, SHUT_RDWR);

		close(connfd);
	}

	close(listenfd);
	printf("======close======\n");
	return 0;
}
