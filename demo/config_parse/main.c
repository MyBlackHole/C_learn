#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "config.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("error, please run with config file\r\n");
		exit(1);
	}

	char *configfile = argv[1];
	printf("config file name:%s\r\n", configfile);

	// 获取绝对路径的 sds
	configfile = getAbsolutePath(configfile);
	if (configfile == NULL) {
		printf("error, getAbsolutePath\r\n");
		exit(1);
	}

	// 载入配置
	loadServerConfig(configfile);

	// 打印配置
	printfRedisConfig();
}
