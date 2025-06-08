#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int demo_connect_main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <port>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int sockfd;
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[1]));
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return EXIT_FAILURE;
	}

	if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("connect");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
