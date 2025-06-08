#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int demo_sendmsg_main(int argc, char *argv[])
{
	int ret; /* 返回值 */
	int sock[2]; /* 套接字对 */
	struct msghdr msg;
	struct iovec iov[1];
	char send_buf[100] = "it is a test";
	struct msghdr msgr;
	struct iovec iovr[1];
	char recv_buf[100];

	/* 创建套接字对 */
	ret = socketpair(AF_LOCAL, SOCK_STREAM, 0, sock);
	if (ret == -1) {
		printf("socketpair err\n");
		return EXIT_FAILURE;
	}

	/* sock[1]发送数据到本地主机  */
	bzero(&msg, sizeof(msg));
	msg.msg_name = NULL; /* void*类型 NULL本地地址*/
	msg.msg_namelen = 0;
	iov[0].iov_base = send_buf;
	iov[0].iov_len = sizeof(send_buf);
	msg.msg_iov = iov; // 要发送或接受数据设为iov
	msg.msg_iovlen = 1; // 1个元素

	printf("开始发送数据：\n");
	printf("发送的数据为: %s\n", send_buf);
	ret = sendmsg(sock[1], &msg, 0);
	if (ret == -1) {
		printf("sendmsg err\n");
		return EXIT_FAILURE;
	}
	printf("发送成功！\n");

	/* 通过sock[0]接收发送过来的数据 */
	bzero(&msg, sizeof(msg));
	msgr.msg_name = NULL;
	msgr.msg_namelen = 0;
	iovr[0].iov_base = &recv_buf;
	iovr[0].iov_len = sizeof(recv_buf);
	msgr.msg_iov = iovr;
	msgr.msg_iovlen = 1;
	ret = recvmsg(sock[0], &msgr, 0);
	if (ret == -1) {
		printf("recvmsg err\n");
		return EXIT_FAILURE;
	}
	printf("接收成功!\n");
	printf("收到数据为: %s\n", recv_buf);

	/* 关闭sockets */
	close(sock[0]);
	close(sock[1]);

	return EXIT_SUCCESS;
}
