#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(EXIT_FAILURE);
}

int demo_gethostbyaddr_main(int argc, char *argv[])
{
	int index;
	struct hostent *host;
	struct sockaddr_in addr;
	if (argc != 2) {
		printf("Usage : %s <IP>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	host = gethostbyaddr((char *)&addr.sin_addr, 4, AF_INET);
	if (!host) {
		error_handling("gethost... error");
	}

	printf("Official name: %s \n", host->h_name);
	for (index = 0; host->h_aliases[index]; index++) {
		printf("Aliases %d:%s \n", index + 1, host->h_aliases[index]);
	}
	printf("Address type: %s \n",
	       (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");

	for (index = 0; host->h_addr_list[index]; index++) {
		printf("IP addr %d: %s \n", index + 1,
		       inet_ntoa(*(struct in_addr *)host->h_addr_list[index]));
	}

	return EXIT_SUCCESS;
}
