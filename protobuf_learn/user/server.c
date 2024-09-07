#include "user_info.pb-c.h"
#include <stdio.h>
#include <string.h>
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
	struct sockaddr_in local_addr = { 0 };
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(9999);
	local_addr.sin_addr.s_addr = INADDR_ANY;

	int ret = bind(fd, (struct sockaddr *)&local_addr, sizeof(local_addr));
	if (ret < 0)
		return -1;

	listen(fd, 5);
	struct sockaddr_in client_addr = { 0 };
	int len = sizeof(client_addr);
	int clientfd = accept(fd, (struct sockaddr *)&client_addr, (socklen_t *)&len);
	if (clientfd < 0)
		return -1;

	int read_size = 0;
	char buf[1024];
	struct msg_proto_header header;
	while (1) {
		memset(&header, 0, sizeof(struct msg_proto_header));
		memset(buf, 0, 1024);
		read_size = recv(clientfd, &header,
				 sizeof(struct msg_proto_header), 0);
		if (read_size < 0) {
			perror("recv fail:");
			break;
		}

		if (header.command == LOGIN_REQUEST && header.length > 0) {
			read_size = recv(clientfd, buf, header.length, 0);
			if (read_size < 0) {
				perror("recv fail:");
				break;
			}
			UserInfo *userInfo =
				user_info__unpack(NULL, header.length, (const uint8_t *)buf);
			if (!userInfo) {
				printf("user_information__unpack is fail!\n");
				continue;
			}
			printf("Unpack: %s %d %d\n", userInfo->name,
			       userInfo->age, userInfo->stat);
			user_info__free_unpacked(userInfo, NULL);
		}
	}
	close(fd);
	return 0;
}
