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
	char msg[1024] = "";

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

	printf("Connected to %s\n", argv[1]);

	scanf("%s", msg);

	ssize_t bytes_sent = recv(sockfd, msg, strlen(msg), 0);

	if (bytes_sent <= 0) {
		perror("recv failed");
		printf("errno: %d\n", errno);
	}

	close(sockfd);
	return 0;
}

/*
python3 -m http.server 6666

❯ xmake run errno_9_demo2 127.0.0.1
Connected to 127.0.0.1
ok
send() failed: Success
errno: 0
*/
