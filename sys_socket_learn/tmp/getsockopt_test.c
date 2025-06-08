#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int s;
	int optval;
	unsigned int optlen = sizeof(int);
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
	}
	getsockopt(s, SOL_SOCKET, SO_TYPE, &optval, &optlen);
	printf("optval = %d\n", optval);
	close(s);
	return 0;
}
