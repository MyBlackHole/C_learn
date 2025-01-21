#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/select.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>

/*设置串口参数*/
static int init_tty(int fd)
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

/* stty -F /dev/ttyUSB0 speed 115200 cs8 -parenb -cstopb -echo */
/* echo "good job!" > /dev/ttyUSB0 */
int demo_demo3_main(int argc, char *argv[])
{
	int fd = 0;
	int len = 0;
	int index = 0;
	char buf[1] = { 0 };

	// 打印串口数据
	// 输出 16 进制数据
	/*FD F4 83 19 44 39 DF*/
	/*FD F4 83 19 48 39 DF*/
	/*FD F4 83 19 42 39 DF*/
	/*FD F4 83 19 41 39 DF*/
	char send_data[4][7];
	send_data[0][0] = 0xFD;
	send_data[0][1] = 0x10;
	send_data[0][2] = 0x83;
	send_data[0][3] = 0x19;
	send_data[0][4] = 0x44;
	send_data[0][5] = 0x60;
	send_data[0][6] = 0xDF;

	send_data[1][0] = 0xFD;
	send_data[1][1] = 0x10;
	send_data[1][2] = 0x83;
	send_data[1][3] = 0x19;
	send_data[1][4] = 0x48;
	send_data[1][5] = 0x60;
	send_data[1][6] = 0xDF;

	send_data[2][0] = 0xFD;
	send_data[2][1] = 0x10;
	send_data[2][2] = 0x83;
	send_data[2][3] = 0x19;
	send_data[2][4] = 0x42;
	send_data[2][5] = 0x60;
	send_data[2][6] = 0xDF;

	send_data[3][0] = 0xFD;
	send_data[3][1] = 0x10;
	send_data[3][2] = 0x83;
	send_data[3][3] = 0x19;
	send_data[3][4] = 0x41;
	send_data[3][5] = 0x60;
	send_data[3][6] = 0xDF;

	// 打开串口
	char *tty = "/dev/ttyUSB0";

	if (argc > 1) {
		tty = argv[1];
	}

	fd = open(tty, O_RDWR);
	if (fd < 0) {
		perror("open failed!");
		return EXIT_FAILURE;
	}
	// 初始化串口
	if (init_tty(fd) != 0) {
		perror("init_tty failed!");
		return EXIT_FAILURE;
	}
	while (1) {
		sleep(10);
		// 发送数据
		len = write(fd, send_data[index % 4], 16);
		if (len < 0) {
			perror("write failed!");
			return EXIT_FAILURE;
		}
		printf("send data: %s\n", send_data[index % 4]);
		index++;
		len = read(fd, buf, sizeof(buf));
		if (len > 0) {
			for (int i = 0; i < len; i++) {
				printf("%02X ", (unsigned char)buf[i]);
			}
			printf("\n");
		} else {
			if (len < 0) {
				perror("read failed!");
				return EXIT_FAILURE;
			}
		}
	}
	close(fd);
	return EXIT_SUCCESS;
}
