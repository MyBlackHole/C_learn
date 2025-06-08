#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(EXIT_FAILURE);
}

int demo_gethostbyname_main(int argc, char *argv[])
{
	int index;
	struct hostent *host;
	if (argc != 2) {
		printf("Usage : %s <addr>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	// 把参数传递给函数，返回结构体
	host = gethostbyname(argv[1]);
	if (!host) {
		error_handling("gethost... error");
	}
	// 输出官方域名
	printf("Official name: %s \n", host->h_name);
	// Aliases 貌似是解析的 cname 域名？
	for (index = 0; host->h_aliases[index]; index++) {
		printf("Aliases %d: %s \n", index + 1, host->h_aliases[index]);
	}
	// 看看是不是ipv4
	printf("Address type: %s \n",
	       (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");
	// 输出ip地址信息
	for (index = 0; host->h_addr_list[index]; index++) {
		printf("IP addr %d: %s \n", index + 1,
		       inet_ntoa(*(struct in_addr *)host->h_addr_list[index]));
	}
	return EXIT_SUCCESS;
}
