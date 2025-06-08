#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define SERVER_PORT 8008

int demo_SO_RCVTIMEO1_client_main()
{
	// 创建socket对象
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// 创建网络通信对象
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	while (1) {
		if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) !=
		    0) {
			printf("连接失败\n");
			exit(EXIT_FAILURE);
		}

		printf("请输入一个数字：");
		char buf = 0;
		scanf("%hhd", &buf);
		if (send(sockfd, &buf, 1, 0) != 1) {
			printf("发送失败\n");
			exit(EXIT_FAILURE);
		}

		printf("等待服务器响应...\n");
		if (recv(sockfd, &buf, 1, 0) != 1) {
			printf("接收失败\n");
			exit(EXIT_FAILURE);
		}

		printf("服务器响应：%hhd\n", buf);
	}
	close(sockfd);
}
