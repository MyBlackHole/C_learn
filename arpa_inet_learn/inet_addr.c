#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

/* inet_addr()函数 */
/* 功能：inet_addr()函数用于将点分十进制IP地址转换成网络字节序IP地址; */
/* 原型：in_addr_t inet_addr(const char *cp); */
/* 返回值：如果正确执行将返回一个无符号长整数型数。如果传入的字符串不是一个合法的IP地址，将返回INADDR_NONE;
 */
int demo_inet_addr_main()
{
	// int i;
	char lo[] = "127.0.0.1";
	struct in_addr netAddr;

	netAddr.s_addr = inet_addr(lo);
	printf("NetIP: 0x%x\n", netAddr.s_addr);

	char *strAddr = inet_ntoa(netAddr);

	printf("StrIP: %s\n", strAddr);
	int ret = inet_aton(strAddr, &netAddr);
	printf("ret = %d, NetIP: 0x%x\n", ret, netAddr.s_addr);
	return 0;
}
