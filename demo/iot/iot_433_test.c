#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "iot_433.h"

int main(int argc, char *argv[])
{
	int fd = 0;

	if (argc < 2) {
		printf("Usage: %s <serial port>\n", argv[0]);
		return EXIT_FAILURE;
	}

	// 打开串口
	fd = open(argv[1], O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd < 0) {
		perror("open failed!");
		return EXIT_FAILURE;
	}

	printf("Serial port %s opened successfully.\n", argv[1]);

	// 初始化串口
	if (iot_init_tty(fd) != 0) {
		perror("init_tty failed!");
		return EXIT_FAILURE;
	}

	printf("Serial port initialized successfully.\n");

	if (iot_send(fd, 0, 0) != 0) {
		perror("send failed!");
		return EXIT_FAILURE;
	}

	printf("Send command successfully.\n");

	// 关闭串口
	if (close(fd) != 0) {
		perror("close failed!");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
