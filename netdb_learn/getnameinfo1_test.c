/* hostname_to_ip hostname */

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM 1025

int demo_getnameinfo1_main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s hostname\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	struct addrinfo hints;
	struct addrinfo *result;
	struct addrinfo *result_pointer;
	int ret;
	/* obtaining address matching host */
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_CANONNAME;
	hints.ai_protocol = 0; /* any protocol */

	ret = getaddrinfo(argv[1], NULL, &hints, &result);
	if (ret != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
		exit(EXIT_FAILURE);
	}
	/* traverse the returned list and output the ip addresses */
	for (result_pointer = result; result_pointer != NULL;
	     result_pointer = result_pointer->ai_next) {
		char hostname[NUM] = "";
		// flags = NI_NUMERICHOST 表示任何情况下都返回数字形式地址
		ret = getnameinfo(result_pointer->ai_addr,
				  result_pointer->ai_addrlen, hostname,
				  sizeof(hostname), NULL, 0, NI_NUMERICHOST);
		if (ret != 0) {
			fprintf(stderr, "error in getnameinfo: %s \n",
				gai_strerror(ret));
			continue;
		}
		printf("IP: %s \n", hostname);
	}
	freeaddrinfo(result);
	exit(EXIT_SUCCESS);
}
