#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

int demo_sendfile_main(int argc, char *argv[])
{
	if (argc <= 3) {
		fprintf(stderr, "%s ip_address port_number filename\n",
			basename(argv[0]));
		return EXIT_FAILURE;
	}
	int ret = 0;
	(void)ret;
	const char *ip = argv[1];
	int port = atoi(argv[2]);
	const char *file_name = argv[3];
	int filefd = open(file_name, O_RDONLY);
	assert(filefd);
	struct stat stat_buf;
	fstat(filefd, &stat_buf);

	struct sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &address);
	address.sin_port = htons(port);
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	assert(sock >= 0);
	int val = 1;

	// 重用正在使用地址
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) ==
	    -1) {
		return EXIT_FAILURE;
	}

	;
	ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
	assert(ret != -1);

	ret = listen(sock, 6);
	assert(ret != -1);

	struct sockaddr_in client;
	socklen_t client_addrlength = sizeof(client);

	int connfd =
		accept(sock, (struct sockaddr *)&client, &client_addrlength);

	if (connfd < 0) {
		fprintf(stderr, "errno is %s\n", strerror(errno));
	} else {
		sendfile(connfd, filefd, NULL, stat_buf.st_size);
		close(connfd);
	}
	close(sock);
	close(filefd);

	return EXIT_SUCCESS;
}
