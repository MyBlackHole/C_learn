#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

/* inet_ntoa()函数 */
/* 功能inet_ntoa()函数用于网络字节序IP转化点分十进制IP; */
/* 原型：char *inet_ntoa (struct in_addr); */
/* 返回值：若无错误发生，inet_ntoa()返回一个字符指针。否则的话，返回NULL。其中的数据应在下一个WINDOWS套接口调用前复制出
 */
int demo_inet_ntoa_main()
{
	/*int i;*/
	char lo[] = "127.0.0.1";
	struct in_addr netAddr;

	netAddr.s_addr = inet_addr(lo);
	printf("NetIP: 0x%x\n", netAddr.s_addr);

	char *strAddr = inet_ntoa(netAddr);

	printf("StrIP: %s\n", strAddr);
	int ret = inet_aton(strAddr, &netAddr);
	printf("ret = %d, NetIP: 0x%x\n", ret, netAddr.s_addr);
	return EXIT_SUCCESS;
}
