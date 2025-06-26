#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int sd;
	int fd;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;
	int str_len;
	int write_len = 1024 * 1024 * 10;
	/*int ret_len = 0;*/
	/*char *write_str = malloc(write_len);*/

	char message[1000];
	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	sd = socket(PF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket() error");
		goto err;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &write_len,
		       sizeof(write_len)) == -1) {
		perror("setsockopt() error");
		goto err_close;
	}

	if (bind(sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
		perror("bind() error");
		goto err_close;
	}

	if (listen(sd, 5) == -1) {
		perror("listen() error");
		goto err_close;
	}

	clnt_addr_size = sizeof(clnt_addr);
	while (1) {
		printf("begin accept\r\n");
		fd = accept(sd, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

		if (fd == -1) {
			// accept系统调用不管检测到有没有可用连接，accept会立马返回
			if (errno == EINTR)
				continue;
			else if (errno == EAGAIN || errno == EWOULDBLOCK) {
				// printf("accept: %s", strerror(errno));
				// 由于是非阻塞(设置了anetNonBlock)方式，accept系统调用没有获取到新连接，则会直接返回，进入这里，不会阻塞

				printf("accept return \r\n");
				// 这里如果不加延时，由于是非阻塞方式，用户态就会不停的accept进行系统调用，会消耗大量CPU
				// 1S后继续accept
				sleep(1);
				// 继续去获取新连接，直到获取到新连接fd，通过break返回退出while循环
				continue;
			} else {
				perror("accept() error");
				goto err_close;
			}
		}
		getc(stdin);
		printf("accept successful from client\r\n\r\n");

		printf("begin recv message\r\n");
		str_len = read(fd, message, sizeof(message) - 1);

		if (str_len == -1) {
			perror("read() error");
			goto err_close1;
		}
		printf("recv len %d \r\n", str_len);
		printf("recv message:%s from client\r\n\r\n", message);

		// getc(stdin);

		close(fd);
	}

	close(sd);

	return EXIT_SUCCESS;
err_close1:
	close(fd);
err_close:
	close(sd);
err:
	return EXIT_FAILURE;
}
