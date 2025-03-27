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
	char buffer[1024];

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

	for (int i = 0; i < 50; i++) {
		recv(sockfd, buffer, sizeof(buffer), 0);
		printf("recv: %s, errno: %d(%s)\n", buffer, errno,
		       strerror(errno));
		sleep(1);
		if (i == 4) {
			shutdown(sockfd, SHUT_RDWR);
			shutdown(sockfd, SHUT_RDWR);
		}
	}

	close(sockfd);
	return 0;
}

/*
❯ xmake run errno_107_server
====== start accept ======
accept: 7
accept: 7

❯ xmake run errno_107_demo1 127.0.0.1
recv: hello, errno: 0(Success)
recv: hello, errno: 0(Success)
recv: hello, errno: 0(Success)
recv: hello, errno: 0(Success)
recv: hello, errno: 0(Success)
recv: hello, errno: 107(Transport endpoint is not connected)
recv: hello, errno: 107(Transport endpoint is not connected)
recv: hello, errno: 107(Transport endpoint is not connected)
recv: hello, errno: 107(Transport endpoint is not connected)
recv: hello, errno: 107(Transport endpoint is not connected)
recv: hello, errno: 107(Transport endpoint is not connected)
recv: hello, errno: 107(Transport endpoint is not connected)
recv: hello, errno: 107(Transport endpoint is not connected)
recv: hello, errno: 107(Transport endpoint is not connected)
recv: hello, errno: 107(Transport endpoint is not connected)
recv: hello, errno: 107(Transport endpoint is not connected)
recv: hello, errno: 107(Transport endpoint is not connected)
recv: hello, errno: 107(Transport endpoint is not connected)
recv: hello, errno: 107(Transport endpoint is not connected)
recv: hello, errno: 107(Transport endpoint is not connected)
recv: hello, errno: 107(Transport endpoint is not connected)
*/
