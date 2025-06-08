#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 1024
// open
// read
// write
// 文件权限由open的mode参数和当前进程的umask掩码共同决定。
// 第三个参数是在第二个参数中有O_CREAT时才作用，如果没有，则第三个参数可以忽略
int demo_open_main(int argc, char *argv[])
{
	int sfd = 0;
	int dfd = 0;
	char buf[BUFSIZE] = { 0 };
	size_t len = 0;
	size_t ret = 0;
	int pos = 0;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s <str_file> <desc_file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	sfd = open(argv[1], O_RDONLY);
	if (sfd < 0) {
		perror("open()");
		exit(EXIT_FAILURE);
	}

	dfd = open(argv[2], O_WRONLY | O_CREAT, O_TRUNC,
		   S_IRWXO | S_IRWXG | S_IRWXU);
	if (dfd < 0) {
		close(sfd);
		perror("open()");
		exit(EXIT_FAILURE);
	}

	while (1) {
		len = read(sfd, buf, BUFSIZE);
		if (len < 0) {
			perror("read()");
			exit(EXIT_FAILURE);
		}
		if (len == 0) {
			break;
		}
		pos = 0;

		// 需要循环,确保写入 len 字节
		while (len > 0) {
			ret = write(dfd, buf + pos, len);
			if (ret < 0) {
				perror("write()");
				exit(EXIT_FAILURE);
			}
			pos += pos;
			len -= ret;
		}
	}

	close(dfd);
	close(sfd);

	exit(EXIT_SUCCESS);
}
