#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>

#define MY_SOCK_PATH "/tmp/mysocket"
#define LISTEN_BACKLOG 50

void send_fd(int socket, int fd_to_send)
{
	struct msghdr message;
	struct iovec iov;
	struct cmsghdr *control_message = NULL;
	char ctrl_buf[CMSG_SPACE(sizeof(int))];
	char data[1];
	memset(&message, 0, sizeof(struct msghdr));
	memset(ctrl_buf, 0, CMSG_SPACE(sizeof(int)));
	/* We are passing at least one byte of data so that recvmsg() will not return 0 */
	data[0] = ' ';
	iov.iov_base = data;
	iov.iov_len = sizeof(data);
	message.msg_name = NULL;
	message.msg_namelen = 0;
	message.msg_iov = &iov;
	message.msg_iovlen = 1;
	message.msg_controllen = CMSG_SPACE(sizeof(int));
	message.msg_control = ctrl_buf;
	control_message = CMSG_FIRSTHDR(&message);
	control_message->cmsg_level = SOL_SOCKET;
	control_message->cmsg_type = SCM_RIGHTS;
	control_message->cmsg_len = CMSG_LEN(sizeof(int));
	*((int *)CMSG_DATA(control_message)) = fd_to_send;
	if (sendmsg(socket, &message, 0) < 0) {
		perror("Failed to send message");
		exit(1);
	}
}

int main(void)
{
	int sfd, cfd, ufd;
	struct sockaddr_in my_addr, peer_addr;
	socklen_t peer_addr_size;
	struct sockaddr_un un_addr;
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	memset(&my_addr, 0, sizeof(struct sockaddr_in));
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = INADDR_ANY;
	my_addr.sin_port = htons(12345);
	if (bind(sfd, (struct sockaddr *)&my_addr,
		 sizeof(struct sockaddr_in)) == -1) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	if (listen(sfd, LISTEN_BACKLOG) == -1) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	/* Accept actual connection from the client */
	peer_addr_size = sizeof(struct sockaddr_in);
	cfd = accept(sfd, (struct sockaddr *)&peer_addr, &peer_addr_size);
	if (cfd == -1) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
	/* Here we would normally do something with the connected socket */
	/* Handle the first message from the client */
	char buffer[1024];
	ssize_t numRead = read(cfd, buffer, sizeof(buffer));
	if (numRead > 0) {
		printf("Process A received message: %.*s\n", (int)numRead,
		       buffer);
		// Send a response with a prefix to the client
		char response[1024];
		int len = snprintf(response, sizeof(response),
				   "Process A: %.*s", (int)numRead, buffer);
		if (write(cfd, response, len) != len) {
			perror("partial/failed write");
			close(cfd);
			close(sfd);
			exit(EXIT_FAILURE);
		}
	} else if (numRead == -1) {
		perror("read");
		close(cfd);
		close(sfd);
		exit(EXIT_FAILURE);
	}
	/* Now we create a UNIX domain socket to send the descriptor to process B */
	ufd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (ufd == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	memset(&un_addr, 0, sizeof(struct sockaddr_un));
	un_addr.sun_family = AF_UNIX;
	strncpy(un_addr.sun_path, MY_SOCK_PATH, sizeof(un_addr.sun_path) - 1);
	if (connect(ufd, (struct sockaddr *)&un_addr,
		    sizeof(struct sockaddr_un)) == -1) {
		perror("connect");
		exit(EXIT_FAILURE);
	}
	/* Send the descriptor */
	send_fd(ufd, cfd);
	/* Close the connected socket and listening socket */
	close(cfd);
	close(sfd);
	return 0;
}
