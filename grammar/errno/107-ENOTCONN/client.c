#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;
	char buf[1024];

	if (argc != 2) {
		printf("usage: ./client <ipaddress>\n");
		return 0;
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("create socket error: %s(errno: %d)\n", strerror(errno),
		       errno);
		return 0;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6666);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
		printf("inet_pton error for %s\n", argv[1]);
		return 0;
	}

	/*if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) <*/
	/*    0) {*/
	/*	printf("connect error: %s(errno: %d)\n", strerror(errno),*/
	/*	       errno);*/
	/*	return 0;*/
	/*}*/

	while (1) {
		if (recv(sockfd, buf, 1024, 0) <= 0) {
			printf("recv error: %s(errno: %d)\n", strerror(errno),
			       errno);
			break;
		}
	}

	return 0;
}

// output:
//
// ❯ xmake run errno_107_client 127.0.0.1
// recv error: Transport endpoint is not connected(errno: 107)
