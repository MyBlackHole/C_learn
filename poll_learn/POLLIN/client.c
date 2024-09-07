
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#define CONTINUE() (errno == EAGAIN || errno == EINTR || errno == EINPROGRESS)

int create_socket()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		fprintf(stderr, "socket fail: %m");
		return sockfd;
	}

	return sockfd;
}

inline static int read_is_ready(int fd, const unsigned int ms)
{
	int ret = 0;
	struct pollfd pfd;
	const int timeout = ms;
	memset(&pfd, 0x00, sizeof(pfd));
	pfd.fd = fd;
	pfd.events = POLLIN;
	if ((ret = poll(&pfd, 1, timeout)) < 0) {
		printf("POLLIN=%d, POLLOUT=%d, POLLERR=%d POLLHUP=%d\n",
		       (pfd.revents & POLLIN) != 0,
		       (pfd.revents & POLLOUT) != 0,
		       (pfd.revents & POLLERR) != 0,
		       (pfd.revents & POLLHUP) != 0);
	} else if (pfd.revents & POLLIN) {
		printf("POLLIN=%d, POLLOUT=%d, POLLERR=%d POLLHUP=%d\n",
		       (pfd.revents & POLLIN) != 0,
		       (pfd.revents & POLLOUT) != 0,
		       (pfd.revents & POLLERR) != 0,
		       (pfd.revents & POLLHUP) != 0);
		return 1;
	} else {
		printf("POLLIN=%d, POLLOUT=%d, POLLERR=%d POLLHUP=%d\n",
		       (pfd.revents & POLLIN) != 0,
		       (pfd.revents & POLLOUT) != 0,
		       (pfd.revents & POLLERR) != 0,
		       (pfd.revents & POLLHUP) != 0);
		fprintf(stderr, "fd: %d, ret: %d, timeout: %d, %s(errno: %d)\n",
			fd, ret, timeout, strerror(errno), errno);
	}
	return EXIT_SUCCESS;
}

int connect_server(int sockfd, const char *host, short port)
{
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	inet_pton(AF_INET, host, &servaddr.sin_addr);

	int ret = connect(sockfd, (const struct sockaddr *)&servaddr,
			  sizeof(servaddr));
	if (ret < 0 && !CONTINUE()) {
		fprintf(stderr, "connect to [%s:%d] fail: %m", host, port);
		return ret;
	}
	return EXIT_SUCCESS;
}

int connect_net(const char *host, short port)
{
	int sockfd = create_socket();
	if (sockfd < 0) {
		return sockfd;
	}

	int ret = connect_server(sockfd, host, port);
	if (ret < 0) {
		close(sockfd);
		return ret;
	}
	return sockfd;
}

int connection_refused()
{
	int ret;
	int read_status = 0;
	char buf[1024];
	int sockfd = connect_net("127.0.0.1", 6666);
	ret = write(sockfd, "hello", 5);
	if (ret <= 0) {
		close(sockfd);
		return EXIT_FAILURE;
	}

	/*struct pollfd pfd = {0};*/
	while (1) {
		read_status = read_is_ready(sockfd, 1000);
		if (!read_status) {
			fprintf(stderr, "read_is_ready fail\n");
			// sleep(1);
			continue;
		}

		int n = recv(sockfd, buf, sizeof(buf), 0);
		if (n < 0) {
			if (CONTINUE()) {
				continue;
			}
			fprintf(stderr, "recv: error: %s\n", strerror(errno));
			perror("recv: error");
			break;
		}
		if (n == 0) {
			fprintf(stdout, "recv: connection closed\n");
			return EXIT_SUCCESS;
		}
		buf[n] = 0;
		printf("recv: %s\n", buf);
		sleep(1);
	}

	// pfd.fd = sockfd;
	// pfd.events = POLLIN | POLLOUT;
	// int ready = poll(&pfd, 1, -1);
	// printf("ready=%d, POLLIN=%d, POLLOUT=%d, POLLERR=%d\n", ready,
	//        (pfd.revents & POLLIN) != 0, (pfd.revents & POLLOUT) != 0,
	//        (pfd.revents & POLLERR) != 0);

	// int error;
	// socklen_t errlen = sizeof(error);
	// getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &errlen);
	// printf("error=%d, msg=%s\n", error, strerror(error));
	close(sockfd);
	return ret;
}

int main(int argc, const char *argv[])
{
	return connection_refused();
}
