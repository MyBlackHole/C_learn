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
int init_tty(int fd)
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
int demo_demo1_main(int argc, char *argv[])
{
	int fd = 0;
	char buf[1024] = { 0 };
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
		// // 清空输入缓冲区
		// // 清空输出缓冲区
		// tcflush(fd, TCIOFLUSH);
		// // 读取串口数据
		int len = read(fd, buf, sizeof(buf));
		if (len > 0) {
			// 打印串口数据
			// 输出 16 进制数据
			// FDF403DC41034ADF k
			// FDF403DC41C04CDF g
			// FDF403DC410C4CDF s
			// FD F4 03 DC 41 30 4C DF t
			for (int i = 0; i < len; i++) {
				printf("%02X ", (unsigned char)buf[i]);
			}
			printf("\n");
		}
	}

	close(fd);
	return EXIT_SUCCESS;
}
