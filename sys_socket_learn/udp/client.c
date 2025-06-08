#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	// 创建socket对象
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	// 创建网络通信对象
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1324);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	while (1) {
		printf("请输入一个数字：");
		char buf = 0;
		scanf("%hhd", &buf);
		sendto(sockfd, &buf, sizeof(buf), 0, (struct sockaddr *)&addr,
		       sizeof(addr));

		socklen_t len = sizeof(addr);
		recvfrom(sockfd, &buf, sizeof(buf), 0, (struct sockaddr *)&addr,
			 &len);

		if (66 == buf) {
			printf(" server 成功接受\n");
		} else {
			printf("server 数据丢失\n");
		}
	}
	close(sockfd);
	return EXIT_SUCCESS;
}
