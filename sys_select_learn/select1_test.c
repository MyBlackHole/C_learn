#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#define BUF_SIZE 30

int demo_select1_main(int argc, char *argv[])
{
	fd_set reads;
	fd_set temps;
	int result;
	int str_len;
	char buf[BUF_SIZE];
	struct timeval timeout;

	// 初始化变量
	FD_ZERO(&reads);
	// 将文件描述符0对应的位设置为1
	FD_SET(0, &reads);

	/*
	 * timeout.tv_sec=5;
	 * timeout.tv_usec=5000;
	 */

	while (1) {
		// 为了防止调用了select 函数后，位的内容改变，先提前存一下
		temps = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		// 如果控制台输入数据，则返回大于0的数，没有就会超时
		result = select(STDOUT_FILENO, &temps, 0, 0, &timeout);
		if (result == -1) {
			puts("select error!");
			break;
		} else if (result == 0) {
			puts("Time-out!");
		} else {
			// 验证发生变化的值是否是标准输入端
			if (FD_ISSET(0, &temps)) {
				str_len = read(0, buf, BUF_SIZE);
				buf[str_len] = 0;
				printf("message from console: %s", buf);
			}
		}
	}
	return 0;
}
