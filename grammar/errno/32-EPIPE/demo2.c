#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servaddr;

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6666);

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
		printf("inet_pton error for %s\n", argv[1]);
		return 0;
	}

	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) <
	    0) {
		printf("connect error: %s(errno: %d)\n", strerror(errno),
		       errno);
		return 0;
	}

	shutdown(sockfd, SHUT_WR); // 关闭写端

	const char *msg = "Hello";
	ssize_t bytes_sent = send(sockfd, msg, strlen(msg), 0);

	if (bytes_sent < 0) {
		perror("send() failed");
		printf("errno: %d\n", errno); // 输出 107 (ENOTCONN)
	}

	close(sockfd);
	return 0;
}

/*
python3 -m http.server 6666

❯ xmake run errno_32_demo2 127.0.0.1
send() failed: Broken pipe
errno: 32
*/
