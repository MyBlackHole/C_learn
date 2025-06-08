#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sd;
	struct sockaddr_in serv_addr;

	char message[] = "block test message";
	(void)message;
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sd = socket(PF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		error_handling("socket() error");
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	printf("begin connect\r\n");
	if (connect(sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) ==
	    -1) {
		error_handling("connect() error\r\n");
	}
	printf("end connect\r\n\r\n");

	// 关闭读端后，服务器端将接收数据大小为0,
	// 原因是因为客户端已经关闭了读端，所以服务器端将收到一个FIN包
	shutdown(sd, SHUT_RD);

	sleep(10);
	close(sd);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputs("\n", stderr);
	exit(1);
}
