#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

/* inet_aton()函数 */
/* 功能：inet_aton()函数用于将点分十进制IP地址转换成网络字节序IP地址; */
/* 原型：int inet_aton(const char *string, struct in_addr *addr); */
/* 返回值：如果这个函数成功，函数的返回值非零，如果输入地址不正确则会返回零; */
int demo_inet_aton_main()
{
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
