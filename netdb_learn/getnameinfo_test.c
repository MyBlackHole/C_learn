#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM 128

int demo_getnameinfo_main(int argc, char *argv[])
{
	int ret;
	char *ptr;
	char hostname[NUM] = { 0 };
	char servername[NUM] = { 0 };
	struct sockaddr_in addr_dst;

	ptr = argc < 2 ? "180.101.49.11" : argv[1];

	memset(&addr_dst, 0, sizeof(addr_dst));
	addr_dst.sin_family = AF_INET;
	addr_dst.sin_addr.s_addr = inet_addr(ptr);

	ret = getnameinfo((struct sockaddr *)&addr_dst, sizeof(addr_dst),
			  hostname, sizeof(hostname), servername,
			  sizeof(servername), 0);
	if (ret != 0) {
		fprintf(stderr, "error in getnameinfo: %s \n",
			gai_strerror(ret));
	} else {
		printf("hostname IP: %s \n", hostname);
		printf("servername IP: %s \n", servername);
	}

	exit(EXIT_SUCCESS);
}
