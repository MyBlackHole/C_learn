#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define exit_if(r, ...)                                               \
	if (r) {                                                      \
		printf(__VA_ARGS__);                                  \
		printf("%s:%d error no: %d error msg %s\n", __FILE__, \
		       __LINE__, errno, strerror(errno));             \
		exit(1);                                              \
	}

void setNonBlock(int fd)
{
	int r;
	int flags;
	flags = fcntl(fd, F_GETFL, 0);
	exit_if(flags < 0, "fcntl failed");
	r = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	exit_if(r < 0, "fcntl failed");
}

void client_handle()
{
	int fd;
	int ret;
	short port = 8000;
	struct sockaddr_in addr;

	memset(&addr, 0, sizeof addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	exit_if(fd < 0, "create socket error");

	ret = connect(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
	exit_if(ret < 0, "connect to server error");
	setNonBlock(fd);

	printf("connect to server success");

	const int LEN = 1024 * 1000;
	char msg[LEN]; // 1MB data
	memset(msg, 'a', LEN);

	for (int i = 0; i < 1000; ++i) {
		int len = send(fd, msg, LEN, 0);
		printf("send: %d, erron: %d, %s \n", len, errno,
		       strerror(errno));
		sleep(1);
	}
}

int demo_client_main()
{
	client_handle();

	return 0;
}

// ❯ ./out/obj/errno_learn/EAGAIN/client
// connect to server successsend: 1024000, erron: 0, Success
// send: 1024000, erron: 0, Success
// send: 1024000, erron: 0, Success
// send: 1024000, erron: 0, Success
// send: 1024000, erron: 0, Success
// send: 1024000, erron: 0, Success
// send: 1024000, erron: 0, Success
// send: 1024000, erron: 0, Success
// send: 1024000, erron: 0, Success
// send: 464082, erron: 0, Success
// send: -1, erron: 11, Resource temporarily unavailable
// send: -1, erron: 11, Resource temporarily unavailable
// send: -1, erron: 11, Resource temporarily unavailable
// send: -1, erron: 11, Resource temporarily unavailable
// send: -1, erron: 11, Resource temporarily unavailable
// send: -1, erron: 11, Resource temporarily unavailable
// send: -1, erron: 11, Resource temporarily unavailable
// send: -1, erron: 11, Resource temporarily unavailable
// send: -1, erron: 104, Connection reset by peer
