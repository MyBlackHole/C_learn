#include <arpa/inet.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define RTY 10

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int ret;
	int sock;
	struct sockaddr_in serv_addr;
	char *message = "BLACK HOLE";
	size_t str_len;

	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < RTY; i++) {
		// 服务端 socket addr 初始化创建
		memset(&serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
		serv_addr.sin_port = htons(atoi(argv[2]));

		// ipv4 协议族 TCP 协议 scok 创建
		sock = socket(PF_INET, SOCK_STREAM, 0);
		if (sock < 0) {
			error_handling("socket() error");
		}

		// 调用 connect 函数向服务器发送连接请求
		// 在服务端队列满后堵塞连接
		printf("start conn!\n");
		ret = connect(sock, (struct sockaddr *)&serv_addr,
			      sizeof(serv_addr));
		if (ret < 0) {
			error_handling("connect() error!");
		}

		printf("start write!\n");
		str_len = write(sock, message, strlen(message) - 1);
		if (str_len == -1) {
			error_handling("read() error!");
		}

		printf("Message from server : %s \n", message);

		// 不关闭 sock
		// close(sock);
	}

	sleep(100);
	return EXIT_SUCCESS;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(EXIT_FAILURE);
}
