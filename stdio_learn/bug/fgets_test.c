#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * pipe 最大缓冲区大小为65536字节，
 * 64KB 即 65536 字节，
 * */
/*#define BUFSIZE 6*/
#define BUFSIZE 65536

#define PATH "/run/media/black/Data/Documents/c/stdio_learn/bug/fgets_test.log"

int main(int argc, char *argv[])
{
	FILE *fps = stdin;
	FILE *fpd = NULL;
	char buf[BUFSIZE];
	int read_size = 0;

	fpd = fopen(PATH, "w");
	if (fpd == NULL) {
		perror("fopen()");
		exit(EXIT_FAILURE);
	}

	printf("start\n");
	sleep(10);
	/*读取 64 KB 大小数据到 buf 缓冲区中*/
	while (read_size < BUFSIZE) {
		read_size +=
			fread(buf + read_size, 1, BUFSIZE - read_size, fps);
		printf("read_size = %d, buf = %s\n", read_size, buf);
		sleep(1);
	}
	fprintf(fpd, "read_size = %d\n", read_size);
	sleep(10);
	/*清空 buf 缓冲区*/
	memset(buf, 0, BUFSIZE);
	read_size = 0;

	/*读取完毕，退出循环*/
	if (feof(fps)) {
		fprintf(fpd, "line = %d, fgets() = %s\n", __LINE__, buf);
	}

	read_size = fread(buf, 1, BUFSIZE, fps);
	fprintf(fpd, "read size = %d, fgets() = %s\n", read_size, buf);

	/*读取完毕，退出循环*/
	if (feof(fps)) {
		fprintf(fpd, "line = %d, fgets() = %s\n", __LINE__, buf);
	}

	fclose(fpd);
	fclose(fps);

	exit(0);
}
