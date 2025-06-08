#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define DATA_COUNT 4
#define MAP_COUNT 2

// 打印串口数据
// 输出 16 进制数据
/*FD F4 83 19 44 39 DF*/
/*FD F4 83 19 48 39 DF*/
/*FD F4 83 19 42 39 DF*/
/*FD F4 83 19 41 39 DF*/
char data_0[DATA_COUNT][7] = {
	// 正门 开、关、锁、停
	{ 0xFD, 0x03, 0x83, 0x19, 0x44, 0x60, 0xDF },
	{ 0xFD, 0x03, 0x83, 0x19, 0x41, 0x60, 0xDF },
	{ 0xFD, 0x03, 0x83, 0x19, 0x42, 0x60, 0xDF },
	{ 0xFD, 0x03, 0x83, 0x19, 0x48, 0x60, 0xDF },
};

/*FD F4 16 EA 04 3A DF*/
/*FD F4 16 EA 01 3A DF*/
/*FD F4 16 EA 08 3A DF*/
/*FD F4 16 EA 02 3A DF*/
char data_1[DATA_COUNT][7] = {
	// 侧正门 开、关、锁、停
	{ 0xFD, 0x03, 0x16, 0xEA, 0x04, 0x60, 0xDF },
	{ 0xFD, 0x03, 0x16, 0xEA, 0x01, 0x60, 0xDF },
	{ 0xFD, 0x03, 0x16, 0xEA, 0x02, 0x60, 0xDF },
	{ 0xFD, 0x03, 0x16, 0xEA, 0x08, 0x60, 0xDF },
};

// 地址映射数组
char *map[MAP_COUNT][DATA_COUNT] = {
	{ data_0[0], data_0[1], data_0[2], data_0[3] },
	{ data_1[0], data_1[1], data_1[2], data_1[3] },
};

int iot_send(int fd, int map_index, int data_index)
{
	int ret = 0;
	int len = 0;
	int j;

	if (fd < 0) {
		printf("fd error\n");
		ret = -EBADF;
		goto exit;
	}

	if (map_index < 0 || map_index >= MAP_COUNT) {
		printf("map_index error\n");
		ret = -EINVAL;
		goto exit;
	}

	if (data_index < 0 || data_index >= DATA_COUNT) {
		printf("data_index error\n");
		ret = -EINVAL;
		goto exit;
	}
	for (j = 0; j < 7; j++) {
		printf("%02x", (unsigned char)map[map_index][data_index][j]);
	}
	printf("\n");

	len = write(fd, map[map_index][data_index], 7);
	if (len != 7) {
		perror("write error");
		ret = -EIO;
		goto exit;
	}

	len = read(fd, &ret, 1);
	if (len != 1) {
		perror("read error");
		ret = -EIO;
		goto exit;
	}

	if (ret != 0xF0) {
		switch (ret) {
		case 0xF4:
			printf("指令错误\n");
			break;
		case 0xF6:
			printf("通电发射已禁止\n");
			break;
		default:
			printf("未知错误, 0x%0x\n", ret);
		}
		ret = -EIO;
		goto exit;
	}
	ret = 0;
exit:
	return ret;
}

int iot_init_tty(int fd)
{
	struct termios termios_rfid = { 0 };

	// 设置终端属性，激活选项
	cfmakeraw(&termios_rfid);
	// 输入波特率
	cfsetispeed(&termios_rfid, B9600);
	// 输出波特率
	cfsetospeed(&termios_rfid, B9600);
	// 本地连接和接收使能
	termios_rfid.c_cflag |= CLOCAL | CREAD;
	// 清空数据位
	termios_rfid.c_cflag &= ~CSIZE;
	// 数据位为8位
	termios_rfid.c_cflag |= CS8;
	// 无奇偶校验
	termios_rfid.c_cflag &= ~PARENB;
	// 一位停止位
	termios_rfid.c_cflag &= ~CSTOPB;

	tcflush(fd, TCIFLUSH);
	// 设置等待时间
	termios_rfid.c_cc[VTIME] = 10;
	termios_rfid.c_cc[VMIN] = 1;
	// 清空输入缓冲区
	tcflush(fd, TCIFLUSH);
	// 激活串口设置
	if (tcsetattr(fd, TCSANOW, &termios_rfid) != 0)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
