#include <arpa/inet.h>
#include <errno.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define INFACE "wlp1s0"
// #define INFACE "enx0203040d3136"
// #define INFACE "lo"
static char *SERVERADDR = "192.168.100.109";
static int SERVERPORT = 8000;

int main()
{
	struct sockaddr_in server_addr;
	int sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		printf("create socket fail \r\n");
		return EXIT_FAILURE;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVERPORT);
	if (inet_aton(SERVERADDR, &server_addr.sin_addr) != 1) {
		printf("addr convert fail \r\n");
		goto free;
	}

	// 指定网络接口
	struct ifreq nif;
	strcpy(nif.ifr_name, INFACE);

	/* 绑定接口 */
	// 指定网卡
	if (setsockopt(sock, SOL_SOCKET, SO_BINDTODEVICE, (char *)&nif,
		       sizeof(nif)) < 0) {
		printf("bind interface fail, errno: %d \r\n", errno);
		return EXIT_FAILURE;
	}

	/* 发送 */
	if (connect(sock, ((struct sockaddr *)&server_addr),
		    sizeof(server_addr)) < 0) {
		printf("addr connect fail \r\n");
		goto free;
	}

	close(sock);
	return EXIT_SUCCESS;
free:
	close(sock);
	return EXIT_FAILURE;
}
