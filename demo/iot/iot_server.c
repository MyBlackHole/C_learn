#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // 添加 htonl/ntohl

#include "iot_433.h"

#define CMD_OK 5
#define CMD_OPEN 0
#define CMD_CLOSE 1
#define CMD_STOP 2
#define CMD_LOCK 3

// C 服务器定义结构体
#pragma pack(1) // 禁用字节对齐
struct Message {
	uint32_t id;
	uint32_t cmd;
	int32_t result;
};
#pragma pack()

// 发送带长度前缀的消息
void send_message(int socket, struct Message *message)
{
	message->id = htole32(message->id);
	message->cmd = htole32(message->cmd);
	message->result = htole32(message->result);
	send(socket, message, sizeof(struct Message), 0); // 再发数据
}

// 接收带长度前缀的消息
void recv_message(int socket, struct Message *message)
{
	recv(socket, message, sizeof(struct Message), 0); // 接收数据
	message->id = le32toh(message->id);
	message->cmd = le32toh(message->cmd);
	message->result = le32toh(message->result);
}

// 主函数
int main(int argc, char *argv[])
{
	char *device = "/dev/ttyUSB0";
	int d_fd = 0;
	int server_fd, new_socket;
	struct sockaddr_in address;
	int ret = 0;
	int opt = 1;
	int addrlen = sizeof(address);
	struct Message request, response;

	if (argc >= 2) {
		device = argv[1];
	}

	// 打开串口
	d_fd = open(device, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (d_fd < 0) {
		perror("open failed!");
		ret = EXIT_FAILURE;
		goto err;
	}
	printf("串口 %s 已打开...\n", device);

	// 初始化串口
	if (iot_init_tty(d_fd) != 0) {
		perror("init_tty failed!");
		ret = EXIT_FAILURE;
		goto free_d_fd;
	}
	printf("串口 %s 初始化成功...\n", device);

	// 创建套接字
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("创建套接字失败");
		ret = EXIT_FAILURE;
		goto free_d_fd;
	}

	// 设置端口复用
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt,
		       sizeof(opt))) {
		perror("设置套接字选项失败");
		ret = EXIT_FAILURE;
		goto free_server_fd;
	}

	// 绑定地址和端口
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(8080);
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("绑定端口失败");
		ret = EXIT_FAILURE;
		goto free_server_fd;
	}

	// 监听
	if (listen(server_fd, 3) < 0) {
		perror("监听失败");
		ret = EXIT_FAILURE;
		goto free_server_fd;
	}

	printf("服务器已启动，监听端口 8080...\n");

	while (true) {
		// 接受连接
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
					 (socklen_t *)&addrlen)) < 0) {
			perror("接受连接失败");
			continue;
		}
		printf("客户端 %s 已连接...\n", inet_ntoa(address.sin_addr));
		// 发送带协议头的消息
		recv_message(new_socket, &request);
		// 处理请求
		printf("客户端请求命令 %d:%d...\n", request.id, request.cmd);

		response.id = request.id;
		response.cmd = request.cmd;
		response.result = CMD_OK;

		ret = iot_send(d_fd, request.id, request.cmd);
		if (ret != 0) {
			perror("send failed!");
			response.result = ret;
		} else {
			response.result = CMD_OK;
		}

		// 发送带协议头的响应
		send_message(new_socket, &response);
		// 关闭连接
		close(new_socket);
	}
free_server_fd:
	close(server_fd);
free_d_fd:
	close(d_fd);
err:
	return ret;
}
