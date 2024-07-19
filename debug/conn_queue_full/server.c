#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>

#define PORT 8000
#define BACKLOG 4

#define TIMESTRSIZE 1024

int main(int argc, char *argv[])
{
	int ret;

	time_t stamp;
	struct tm *t_tm;
	char timestr[TIMESTRSIZE];

	int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd < 0) {
		perror("Create Socket Error");
		goto ERR;
	}
	struct sockaddr_in server;
	memset(&server, 0, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(listen_fd, (struct sockaddr *)&server,
		   sizeof(struct sockaddr_in));
	if (ret < 0) {
		perror("Bind Error");
		goto ERR;
	}

	ret = listen(listen_fd, BACKLOG);
	if (ret < 0) {
		perror("Listen Error");
		goto ERR;
	}
	while (1) {
		sleep(1);
		stamp = time(NULL);
		t_tm = localtime(&stamp);
		strftime(timestr, TIMESTRSIZE, "NOW:%Y-%m-%d %H:%I:%S", t_tm);
		printf("%s\n", timestr);
	}
	return EXIT_SUCCESS;

ERR:
	close(listen_fd);
	return EXIT_FAILURE;
}
