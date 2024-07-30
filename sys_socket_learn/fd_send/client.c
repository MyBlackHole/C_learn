#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <fcntl.h>

#define UNIXSTR_PATH "foo.socket"
#define OPEN_FILE "test"

int main(int argc, char *argv[])
{
	int clifd;
	// IPC
	struct sockaddr_un servaddr;
	int ret;
	struct msghdr msg;
	struct iovec iov[1];
	char buf[100];
	// 保证cmsghdr和msg_control对齐
	union {
		struct cmsghdr cm;
		char control[CMSG_SPACE(sizeof(int))];
	} control_un;
	struct cmsghdr *pcmsg;
	int fd;

	clifd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (clifd < 0) {
		printf("socket failed.\n");
		return EXIT_FAILURE;
	}

	fd = open(OPEN_FILE, O_CREAT | O_RDWR, 0777);
	if (fd < 0) {
		printf("open test failed.\n");
		return EXIT_FAILURE;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_UNIX;
	strcpy(servaddr.sun_path, UNIXSTR_PATH);

	ret = connect(clifd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if (ret < 0) {
		printf("connect failed.\n");
		return EXIT_SUCCESS;
	}
	// udp需要,tcp无视
	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	iov[0].iov_base = buf;
	iov[0].iov_len = 100;
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;
	// 设置缓冲区和长度
	msg.msg_control = control_un.control;
	msg.msg_controllen = sizeof(control_un.control);
	// 直接通过CMSG_FIRSTHDR取得附属数据
	pcmsg = CMSG_FIRSTHDR(&msg);
	pcmsg->cmsg_len = CMSG_LEN(sizeof(int));
	pcmsg->cmsg_level = SOL_SOCKET;
	// 指明发送的是描述符
	pcmsg->cmsg_type = SCM_RIGHTS;
	// // 把描述符写入辅助数据
	// *((int *)CMSG_DATA(pcmsg)) == fd;
	memcpy(CMSG_DATA(pcmsg), &fd, sizeof(int));

	ret = sendmsg(clifd, &msg, 0); // send filedescriptor
	if (ret < 0) {
		printf("sendmsg failed, errno = %d, %s\n", errno,
		       strerror(errno));
		return EXIT_FAILURE;
	}
	printf("ret = %d, filedescriptor = %d\n", ret, fd);
	close(fd);
	return EXIT_SUCCESS;
}
