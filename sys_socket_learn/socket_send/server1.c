#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define MY_SOCK_PATH "/tmp/mysocket"
#define BUFFER_SIZE 1024

int recv_fd(int socket)
{
	int received_fd;
	struct msghdr message;
	struct iovec iov;
	struct cmsghdr *control_message = NULL;
	char ctrl_buf[CMSG_SPACE(sizeof(int))];
	char data[1];
	int res;
	memset(&message, 0, sizeof(struct msghdr));
	memset(ctrl_buf, 0, CMSG_SPACE(sizeof(int)));
	iov.iov_base = data;
	iov.iov_len = sizeof(data);
	message.msg_name = NULL;
	message.msg_namelen = 0;
	message.msg_iov = &iov;
	message.msg_iovlen = 1;
	message.msg_control = ctrl_buf;
	message.msg_controllen = CMSG_SPACE(sizeof(int));
	if ((res = recvmsg(socket, &message, 0)) <= 0) {
		return -1;
	}
	control_message = CMSG_FIRSTHDR(&message);
	if ((control_message->cmsg_level == SOL_SOCKET) &&
	    (control_message->cmsg_type == SCM_RIGHTS)) {
		received_fd = *((int *)CMSG_DATA(control_message));
	} else {
		received_fd = -1;
	}
	return received_fd;
}

int main(void)
{
	int ufd, fd;
	struct sockaddr_un un_addr;
	char buffer[BUFFER_SIZE];
	ssize_t numRead;
	ufd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (ufd == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	memset(&un_addr, 0, sizeof(struct sockaddr_un));
	un_addr.sun_family = AF_UNIX;
	strncpy(un_addr.sun_path, MY_SOCK_PATH, sizeof(un_addr.sun_path) - 1);
	if (bind(ufd, (struct sockaddr *)&un_addr,
		 sizeof(struct sockaddr_un)) == -1) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	/* Receive the file descriptor from process A */
	fd = recv_fd(ufd);
	if (fd == -1) {
		perror("recv_fd");
		exit(EXIT_FAILURE);
	}
	/* Now we can use the received file descriptor to read data sent by the client */
	while ((numRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
		printf("Process B received message: %.*s\n", (int)numRead,
		       buffer);
		// Send a response with a prefix to the client
		char response[BUFFER_SIZE];
		int len = snprintf(response, sizeof(response),
				   "Process B: %.*s", (int)numRead, buffer);
		if (write(fd, response, len) != len) {
			perror("partial/failed write");
			exit(EXIT_FAILURE);
		}
	}
	if (numRead == -1) {
		perror("read");
		exit(EXIT_FAILURE);
	}
	close(fd);
	close(ufd);
	unlink(MY_SOCK_PATH);
	return 0;
}
