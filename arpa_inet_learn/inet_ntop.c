#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>

int demo_inet_ntop_main(void)
{
	// 存放点分十进制IP地址
	char IPdotdec[20];
	// IPv4地址结构体
	struct in_addr s;
	// 输入IP地址
	printf("Please input IP address: ");
	scanf("%s", IPdotdec);
	// 转换
	inet_pton(AF_INET, IPdotdec, (void *)&s);
	// 注意得到的字节序
	printf("inet_pton: 0x%x\n", s.s_addr);
	// 反转换
	inet_ntop(AF_INET, (void *)&s, IPdotdec, 16);
	printf("inet_ntop: %s\n", IPdotdec);
	return EXIT_SUCCESS;
}
