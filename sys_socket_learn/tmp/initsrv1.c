#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen)
{
	int fd;
	int err = 0;

	fd = socket(addr->sa_family, type, 0);
	if (fd < 0) {
		return EXIT_FAILURE;
	}
	if (bind(fd, addr, alen) < 0) {
		goto errout;
	}
	if (type == SOCK_STREAM || type == SOCK_SEQPACKET) {
		if (listen(fd, qlen) < 0) {
			goto errout;
		}
	}
	return (fd);

errout:
	err = errno;
	close(fd);
	errno = err;
	return (-1);
}
