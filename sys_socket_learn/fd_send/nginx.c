#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stddef.h>
#include <sys/socket.h>

int read_fd(int s, int *fd)
{
	size_t n;
	int err;
	char buf[100];
	struct iovec iov[1];
	struct msghdr msg;

	union {
		struct cmsghdr cm;
		char space[CMSG_SPACE(sizeof(int))];
	} cmsg;

	iov[0].iov_base = buf;
	iov[0].iov_len = 100;

	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;

	msg.msg_control = (caddr_t)&cmsg;
	msg.msg_controllen = sizeof(cmsg);

	n = recvmsg(s, &msg, 0);

	if (n == -1) {
		err = errno;
		if (err == EAGAIN) {
			return err;
		}

		return err;
	}

	if (n == 0) {
		return EXIT_FAILURE;
	}

	if (cmsg.cm.cmsg_len != CMSG_LEN(sizeof(int))) {
		return EXIT_FAILURE;
	}

	memcpy(fd, CMSG_DATA(&cmsg.cm), sizeof(int));

	return EXIT_SUCCESS;
}

int write_fd(int s, int *fd)
{
	ssize_t n;
	int err;
	struct iovec iov[1];
	char buf[100];
	struct msghdr msg;

	union {
		struct cmsghdr cm;
		char space[CMSG_SPACE(sizeof(int))];
	} cmsg;

	msg.msg_control = (caddr_t)&cmsg;
	msg.msg_controllen = sizeof(cmsg);

	memset(&cmsg, 0, sizeof(cmsg));

	cmsg.cm.cmsg_len = CMSG_LEN(sizeof(int));
	cmsg.cm.cmsg_level = SOL_SOCKET;
	cmsg.cm.cmsg_type = SCM_RIGHTS;

	memcpy(CMSG_DATA(&cmsg.cm), fd, sizeof(int));

	msg.msg_flags = 0;

	iov[0].iov_base = buf;
	iov[0].iov_len = 100;

	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;

	n = sendmsg(s, &msg, 0);

	if (n == -1) {
		err = errno;
		if (err == EAGAIN) {
			return err;
		}

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
