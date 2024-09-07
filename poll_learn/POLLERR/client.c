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

#define ASYNC_CONTINUE() \
	(errno == EAGAIN || errno == EINTR || errno == EINPROGRESS)

int fcntl_enable(int sockfd, int feature)
{
	int flags = fcntl(sockfd, F_GETFL, 0);
	if (flags < 0) {
		return flags;
	}

	int ret = fcntl(sockfd, F_SETFL, flags | feature);
	if (ret < 0) {
		return ret;
	}
	return 0;
}

int async_socket()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		fprintf(stderr, "socket fail: %m");
		return sockfd;
	}

	int ret = fcntl_enable(sockfd, O_NONBLOCK);
	if (ret < 0) {
		fprintf(stderr, "fcntl enable nonblock fail: %m");
		close(sockfd);
		return ret;
	}
	return sockfd;
}

int async_connect(int sockfd, const char *host, short port)
{
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	inet_pton(AF_INET, host, &servaddr.sin_addr);

	int ret = connect(sockfd, (const struct sockaddr *)&servaddr,
			  sizeof(servaddr));
	if (ret < 0 && !ASYNC_CONTINUE()) {
		fprintf(stderr, "connect to [%s:%d] fail: %m", host, port);
		return ret;
	}
	return 0;
}

int async_net(const char *host, short port)
{
	int sockfd = async_socket();
	if (sockfd < 0) {
		return sockfd;
	}

	int ret = async_connect(sockfd, host, port);
	if (ret < 0) {
		close(sockfd);
		return ret;
	}
	return sockfd;
}

int connection_refused()
{
	int sockfd = async_net("127.0.0.1", 6666);
	struct pollfd pfd;
	pfd.fd = sockfd;
	pfd.events = POLLIN | POLLOUT;
	int ready = poll(&pfd, 1, -1);
	printf("ready=%d, POLLIN=%d, POLLOUT=%d, POLLERR=%d\n", ready,
	       (pfd.revents & POLLIN) != 0, (pfd.revents & POLLOUT) != 0,
	       (pfd.revents & POLLERR) != 0);

	int error;
	socklen_t errlen = sizeof(error);
	getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &errlen);
	printf("error=%d, msg=%s\n", error, strerror(error));
	return 0;
}

int main(int argc, const char *argv[])
{
	connection_refused();
	return 0;
}
