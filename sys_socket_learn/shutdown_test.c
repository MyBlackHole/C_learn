#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// shutdown() 立即关闭socket;
//  并可以用来唤醒等待线程;
// close() 不一定立即关闭socket(如果有人引用, 要等到引用解除);
// 不会唤醒等待线程

#define BUF_SIZE 30
void error_(char *message);
void read_routine(int sock, char *buf);
void write_routine(int sock, char *buf);

int demo_shutdown_main(int argc, char *argv[])
{
	int sock;
	pid_t pid;
	char buf[BUF_SIZE];
	struct sockaddr_in serv_adr;
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	fprintf(stdout, "pid: %d\n", getpid());

	sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) ==
	    -1) {
		error_("connect() error!");
	}

	printf("connect SUCCESS");
	pid = fork();
	if (pid == 0) {
		write_routine(sock, buf);
	} else {
		read_routine(sock, buf);
	}

	close(sock);
	return EXIT_SUCCESS;
}

void read_routine(int sock, char *buf)
{
	int str_len;
	while (1) {
		str_len = read(sock, buf, BUF_SIZE);
		if (str_len == 0) {
			return;
		}

		if (str_len < 0) {
			fprintf(stderr, "%s\n", strerror(errno));
			break;
		}

		buf[str_len] = 0;
		printf("Message from server: %s", buf);
	}
}
void write_routine(int sock, char *buf)
{
	ssize_t str_len;
	while (1) {
		fgets(buf, BUF_SIZE, stdin);
		if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n")) {
			// 向服务器端传递 EOF,因为 fork
			// 函数复用了文件描述度，所以通过1次close调用不够
			shutdown(sock, SHUT_WR);

			return;
		}

		str_len = write(sock, buf, strlen(buf));

		if (str_len < 0) {
			fprintf(stderr, "%s\n", strerror(errno));
			break;
		}
	}
}

void error_(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
