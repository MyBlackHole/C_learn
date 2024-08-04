#include "user_info.pb-c.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

struct msg_proto_header {
	uint8_t version;
	uint16_t command;
	uint32_t length;
};
enum MSG_COMMOND {
	LOGIN_REQUEST,
};

int main()
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
		return -1;

	struct sockaddr_in server_addr = { 0 };
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9999);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int ret = connect(fd, (struct sockaddr *)&server_addr,
			  sizeof(server_addr));
	if (ret < 0) {
		printf("connect fail!\n");
		return -1;
	}

	uint8_t buffer[1024] = { 0 };
	UserInfo user;
	user_info__init(&user);
	user.name = "dabai";
	user.age = 18;
	user.stat = USER_STATUS__IDLE;

	size_t length = user_info__pack(&user, buffer);
	struct msg_proto_header msg_header;
	msg_header.version = 0x01;
	msg_header.command = LOGIN_REQUEST;
	msg_header.length = length;

	//每隔5s发送一次数据包
	while (1) {
		send(fd, &msg_header, sizeof(struct msg_proto_header), 0);
		send(fd, buffer, length, 0);
		sleep(5);
	}
	close(fd);
	return 0;
}
