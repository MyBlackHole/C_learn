#include "comm.h"
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "config.h"

#define MAXLINE 4096

int main(int argc, char **argv)
{
	int ret;
	int sockfd;
	char recvline[MAXLINE] = { 0 };
	int recvlen = 0;
	struct sockaddr_in servaddr;

	config_t *p_config = NULL;
	configs_t *p_configs = NULL;
	int shmid = GetShm(sizeof(configs_t));
	p_configs = (configs_t *)shmat(shmid, NULL, 0);
	p_config = &p_configs->config[TEST1];
	(void)p_config;

	if (argc != 2) {
		printf("usage: ./client <ipaddress>\n");
		return EXIT_FAILURE;
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		printf("create socket error: %s(errno: %d)\n", strerror(errno),
		       errno);
		ret = sockfd;
		goto err_shmdt;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6666);
	ret = inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	if (ret <= 0) {
		printf("inet_pton error for %s\n", argv[1]);
		goto err_socket;
	}

	ret = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	if (ret < 0) {
		printf("connect error: %s(errno: %d)\n", strerror(errno),
		       errno);
		goto err_socket;
	}

	while (true) {
		printf("recv server msg: \n");
		recvlen = recv(sockfd, recvline, MAXLINE, 0);
		if (recvlen < 0) {
			printf("send msg error: %s(errno: %d)\n",
			       strerror(errno), errno);
			ret = -1;
			goto err_socket;
		}
	}
err_socket:
	close(sockfd);
err_shmdt:
	shmdt(p_configs);
	return ret;
}
