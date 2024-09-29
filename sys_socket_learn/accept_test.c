#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int demo_accept_main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s <listen_fd>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int client_fd;
	int listen_fd = atoi(argv[1]);
	char client_addr[INET_ADDRSTRLEN];
	struct in_addr ip_addr;
	struct sockaddr_in cli;
	socklen_t len = sizeof(struct sockaddr_in);

	printf("Waiting for client to connect...\n");
	client_fd = accept(listen_fd, (struct sockaddr *)&cli, &len);
	ip_addr = cli.sin_addr;
	inet_ntop(AF_INET, &ip_addr, client_addr, INET_ADDRSTRLEN);
	printf("Client Address is : %s\n", client_addr);
	close(client_fd);

	return EXIT_SUCCESS;
}
