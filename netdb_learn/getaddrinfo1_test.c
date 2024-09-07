#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 500
#define IPV6 6
#define IPV4 4

int demo_getaddrinfo1_main(int argc, char *argv[])
{
	struct addrinfo hints;
	struct addrinfo *result;
	struct addrinfo *next;
	/*int sfd;*/
	int ret;
	/*size_t len;*/
	/*ssize_t nread;*/
	char buf[BUF_SIZE];
	struct sockaddr_in *ipv4;
	struct sockaddr_in6 *ipv6;

	/* Obtain address(es) matching host/port */
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC; /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	// hints.ai_flags = AI_ALL;
	hints.ai_protocol = IPPROTO_TCP;

	ret = getaddrinfo(NULL, "10000", &hints, &result);
	if (ret != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
		exit(EXIT_FAILURE);
	}

	for (next = result; next != NULL; next = next->ai_next) {
		switch (next->ai_family) {
		case AF_INET:
			ipv4 = (struct sockaddr_in *)next->ai_addr;
			inet_ntop(next->ai_family, &ipv4->sin_addr, buf,
				  sizeof(buf));
			break;
		case AF_INET6:
			ipv6 = (struct sockaddr_in6 *)next->ai_addr;
			inet_ntop(next->ai_family, &ipv6->sin6_addr, buf,
				  sizeof(buf));
			break;
		default:
			fprintf(stderr, "未知协议族: [%d]\n", next->ai_family);
			exit(EXIT_FAILURE);
		}

		printf("[IPv%d]%s\n", next->ai_family == AF_INET ? IPV4 : IPV6,
		       buf);
	}

	/* No longer needed */
	freeaddrinfo(result);

	exit(EXIT_SUCCESS);
}
