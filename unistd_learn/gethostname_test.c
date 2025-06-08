#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define ERR_EXIT(m)                 \
	do {                        \
		perror(m);          \
		exit(EXIT_FAILURE); \
	} while (0);

#define NUM 100

int demo_gethostname_main(void)
{
	// char host[100] = {0};
	// if (gethostname(host, sizeof(host)) < 0)
	// {
	//     ERR_EXIT("gethostname");
	// }

	// printf("gethostname: %s\n", host);

	char host[NUM] = "aio.backup.com";

	struct hostent *hosts;
	hosts = gethostbyname(host);
	if (hosts == NULL) {
		ERR_EXIT("gethostbyname");
	}

	int index = 0;
	while (hosts->h_addr_list[index] != NULL) {
		printf("hostname: %s\n", hosts->h_name);
		printf("    ip:%s\n",
		       inet_ntoa(*(struct in_addr *)hosts->h_addr_list[index]));
		index++;
	}
	return EXIT_SUCCESS;
}
