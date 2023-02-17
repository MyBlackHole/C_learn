#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 500

int main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s, j;
    size_t len;
    ssize_t nread;
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

    s = getaddrinfo(NULL, "10000", &hints, &result);
    if (s != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        switch (rp->ai_family)
        {
        case AF_INET:
            ipv4 = (struct sockaddr_in *)rp->ai_addr;
            inet_ntop(rp->ai_family, &ipv4->sin_addr, buf, sizeof(buf));
            break;
        case AF_INET6:
            ipv6 = (struct sockaddr_in6 *)rp->ai_addr;
            inet_ntop(rp->ai_family, &ipv6->sin6_addr, buf, sizeof(buf));
            break;
        }

        printf("[IPv%d]%s\n", rp->ai_family == AF_INET ? 4 : 6, buf);
    }

    /* No longer needed */
    freeaddrinfo(result);

    exit(EXIT_SUCCESS);
}
