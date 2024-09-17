#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// 32k
#define BUF 32768

int demo_splice1_main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("usage: %s <file>\n", argv[0]);
		return 1;
	}
	size_t ret = 0;
	int filefd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC,
			  S_IRWXO | S_IRWXG | S_IRWXU);
	assert(filefd > 0);

	// printf("errno:%s\n", strerror(errno));
	// 使用splice时， fd_in和fd_out中必须至少有一个是管道文件描述符。
	ret = splice(STDIN_FILENO, NULL, filefd, NULL, BUF, 0);
	printf("errno:%s\n", strerror(errno));
	assert(ret != -1);

	printf("errno:%d\n", errno);

	assert(ret != -1);
	printf("splice write %ld bytes to file %s\n", ret, argv[1]);

	close(filefd);
	return 0;
}
