#include <getopt.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define LISTEN_QUEUE_N 64

static int listen_fd;
static int server_port;

void listen_server()
{
	int ret;
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server;
	memset(&server, 0, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(server_port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(listen_fd, (struct sockaddr *)&server,
		   sizeof(struct sockaddr_in));

	if (ret < 0) {
		perror("Bind Error");
		exit(EXIT_FAILURE);
	}
	ret = listen(listen_fd, LISTEN_QUEUE_N);

	if (ret < 0) {
		perror("Listen Error");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[])
{
	printf("start shell app\n");
	char *host;
	int port;
	int one_c;
	int option_index = 0;

	static struct option long_options[] = {
		{ "host", required_argument, NULL, 'h' },
		{ "port", required_argument, NULL, 'p' },
		{ 0, 0, 0, 0 }
	};

	while ((one_c = getopt_long(argc, argv, "h:p:", long_options,
				    &option_index)) != -1) {
		switch (one_c) {
			// case 0:
			//     printf("option %s", long_options[option_index].name);
			//     if (optarg)
			//     {
			//         printf(" with arg %s", optarg);
			//     }
			//     printf("\n");
			//     break;

		case 'p':
			port = atoi(optarg);
			printf("option port %d\n", port);
			break;
		case 'h':
			host = optarg;
			printf("option host %s\n", host);
			break;
		default:
			printf(" 未知 %c \n", one_c);
		}
	}
	return EXIT_SUCCESS;
}
