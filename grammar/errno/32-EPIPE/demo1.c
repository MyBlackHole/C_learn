#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>

int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	const char *msg = "Hello";
	ssize_t bytes_sent = send(sockfd, msg, strlen(msg), 0);

	if (bytes_sent < 0) {
		perror("send() failed");
		printf("errno: %d\n", errno); // 输出 107 (ENOTCONN)
	}

	close(sockfd);
	return 0;
}
