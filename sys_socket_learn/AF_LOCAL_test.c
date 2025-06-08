#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

int demo_AF_LOCAL_main()
{
	int fd = socket(AF_LOCAL, SOCK_STREAM, 0);

	unlink("server.socket");

	struct sockaddr_un serv;
	strcpy(serv.sun_path, "server.socket");
	serv.sun_family = AF_LOCAL;
	int ret = bind(fd, (struct sockaddr *)&serv, sizeof(serv));
	if (ret == -1) {
		perror("bind error");
		exit(1);
	}

	listen(fd, 64);

	struct sockaddr_un cli;
	socklen_t len;
	int cfd = accept(fd, (struct sockaddr *)&cli, &len);

	while (1) {
		char buf[64];
		ret = recv(cfd, buf, sizeof(buf), 0);
		if (ret == -1) {
			perror("recv error");
			exit(1);
		} else if (ret == 0) {
			printf("client closed\n");
			close(cfd);
		}
		printf("clinet path:%s\n", cli.sun_path);
		write(STDOUT_FILENO, buf, ret);
	}

	close(cfd);
	close(fd);
	return EXIT_SUCCESS;
}
