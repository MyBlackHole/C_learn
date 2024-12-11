#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int demo_listen_main(int argc, char *argv[])
{
	int ret;
	char client_addr[INET_ADDRSTRLEN];
	int client_fd;
	struct in_addr ip_addr;

	int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd < 0) {
		perror("Create Socket Error");
		goto ERR;
	}
	struct sockaddr_in server;
	memset(&server, 0, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(8000);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(listen_fd, (struct sockaddr *)&server,
		   sizeof(struct sockaddr_in));
	if (ret < 0) {
		perror("Bind Error");
		goto ERR;
	}

	ret = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &ret,
			 sizeof(int));
	if (ret < 0) {
		perror("Setsockopt Error");
		goto ERR;
	}

	ret = listen(listen_fd, 64);
	if (ret < 0) {
		perror("Listen Error");
		goto ERR;
	}
	while (1) {
		struct sockaddr_in cli;
		socklen_t len = sizeof(struct sockaddr_in);
		client_fd = accept(listen_fd, (struct sockaddr *)&cli, &len);
		ip_addr = cli.sin_addr;
		inet_ntop(AF_INET, &ip_addr, client_addr, INET_ADDRSTRLEN);
		printf("Client Address is : %s\n", client_addr);
		close(client_fd);
	}
	return EXIT_SUCCESS;

ERR:
	close(listen_fd);
	return EXIT_FAILURE;
}

// OUPUT: (未加监听复用)
// // 第一个运行正常
// xmake run sys_socket_learn listen
// // 第二个运行异常
// xmake run sys_socket_learn listen
// Bind Error: Address already in use
//
// OUPUT: (加 SO_REUSEADDR (地址复用))
// // 第一个运行正常
// xmake run sys_socket_learn listen
// // 第二个运行异常
// xmake run sys_socket_learn listen
// Bind Error: Address already in use
