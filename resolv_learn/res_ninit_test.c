#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <netinet/in.h>
#include <resolv.h>
#include <stdlib.h>

#define NUM 256

int demo_res_ninit_main()
{
	res_state res = malloc(sizeof(*res));
	res_ninit(res);
	int index = 0;
	/* res->nscount存储了域名服务器的个数 */
	for (index = 0; index < res->nscount; index++) {
		/* 域名服务器的地址 */
		struct sockaddr_in addr = res->nsaddr_list[index];
		char *str_addr = inet_ntoa(addr.sin_addr);
		printf("P: %p, IP: %s, PORT: %d\n", str_addr, str_addr,
		       ntohs(addr.sin_port));
	}
	// exit(0);
	int class = C_IN;
	int type = T_A;
	unsigned char answer[NUM] = "";

	/* answer中为域名解析的结果 */
	int num = res_nquery(res, "www.baidu.com", class, type, answer,
			     sizeof(answer));
	res_nclose(res);
	for (int i = 0; i < num; i++) {
		printf("%02x", answer[i]);
	}
	exit(0);
}
