#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	struct sockaddr_in serverAddr;
	char buffer[1024];
	int sock, retl;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	assert(sock >= 0);

	bzero(&serverAddr, sizeof(serverAddr));

	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(6611);
	serverAddr.sin_family = AF_INET;
	retl = connect(sock, (const struct sockaddr *)&serverAddr,
		       (socklen_t)sizeof(struct sockaddr));
	assert(retl >= 0);

	retl = 0;
	while (1) {
		retl++;
		sprintf(buffer, "This is frame number %d", retl);
		send(sock, buffer, strlen(buffer), 0);
		sleep(1);
	}

	return 0;
}
