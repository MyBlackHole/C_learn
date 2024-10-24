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
	int client_id = 0;
	char *ipaddress = NULL;
	int port = 0;
	struct sockaddr_in servaddr;

	configs_t *p_configs = NULL;
	config_t *p_config = NULL;

	if (argc != 4) {
		printf("usage: ./client <ipaddress> <port> <client_id>\n");
		return EXIT_FAILURE;
	}

	ipaddress = argv[1];
	port = atoi(argv[2]);
	client_id = atoi(argv[3]);

	p_configs = get_configs();
	if (p_configs == NULL) {
		printf("get_configs error\n");
		return EXIT_FAILURE;
	}

	p_config = get_config(p_configs, client_id);

	cnofig_init(p_config);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		printf("create socket error: %s(errno: %d)\n", strerror(errno),
		       errno);
		ret = sockfd;
		goto err_shmdt;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	ret = inet_pton(AF_INET, ipaddress, &servaddr.sin_addr);
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
		config_get_dowload_speed(p_config);
		recvlen = recv(sockfd, recvline, MAXLINE, 0);
		if (recvlen < 0) {
			printf("send msg error: %s(errno: %d)\n",
			       strerror(errno), errno);
			ret = recvlen;
			goto err_socket;
		}
		if (recvlen == 0) {
			printf("server closed\n");
			break;
		}
		recvline[recvlen] = 0;
		printf("recv len: %d\n", recvlen);
		config_update_bandwidth(p_config, recvlen);
	}
err_socket:
	close(sockfd);
err_shmdt:
	chmdt_configs(p_configs);
	return ret;
}
