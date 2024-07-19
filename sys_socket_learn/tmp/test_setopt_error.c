#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

int main()
{
	int fd;
	int sockopt = 1;
	int res;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		printf("create socket error!\n");
		exit(-1);
	}

	// sleep(20);

	printf("close socket\n");
	close(fd);

	res = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof(int));
	if (res < 0) {
		perror(strerror(errno));
		exit(-1);
	}

	close(fd);

	exit(0);
}
