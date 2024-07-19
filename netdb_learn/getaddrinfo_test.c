#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 500
#define IPV6 6
#define IPV4 4

int demo_getaddrinfo_main(int argc, char *argv[])
{
	struct addrinfo hints;
	struct addrinfo *result;
	struct addrinfo *res;
	int status;
	// int sfd, j;
	// size_t len;
	// ssize_t nread;
	char buf[BUF_SIZE];
	struct sockaddr_in *ipv4;
	struct sockaddr_in6 *ipv6;

	/* Obtain address(es) matching host/port */
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC; /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_ALL;
	hints.ai_protocol = IPPROTO_TCP;

	status = getaddrinfo("192.168.100.179", NULL, &hints, &result);
	// status = getaddrinfo("www.bilibili.com", "https", &hints, &result);
	if (status != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		exit(EXIT_FAILURE);
	}

	for (res = result; res != NULL; res = res->ai_next) {
		switch (res->ai_family) {
		case AF_INET:
			ipv4 = (struct sockaddr_in *)res->ai_addr;
			inet_ntop(res->ai_family, &ipv4->sin_addr, buf,
				  sizeof(buf));
			break;
		case AF_INET6:
			ipv6 = (struct sockaddr_in6 *)res->ai_addr;
			inet_ntop(res->ai_family, &ipv6->sin6_addr, buf,
				  sizeof(buf));
			break;
		default:
			fprintf(stderr, "未知协议族: [%d]\n", res->ai_family);
			exit(EXIT_FAILURE);
		}

		printf("[IPv%d]%s\n", res->ai_family == AF_INET ? IPV4 : IPV6,
		       buf);
	}

	/* No longer needed */
	freeaddrinfo(result);

	exit(EXIT_SUCCESS);
}
