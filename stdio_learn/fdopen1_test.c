#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int demo_fdopen1_main(int argc, char *argv[])
{
	FILE *file_fp;
	char *name = "/data.dat";
	char *path = dirname(argv[0]);
	char *file_path = malloc(strlen(name) + strlen(path));
	strcpy(file_path, path);
	strcat(file_path, name);
	// 创建文件并返回文件描述符
	int fd_tmp = open(file_path, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd_tmp <= 0) {
		fputs("file open error", stdout);
		return EXIT_FAILURE;
	}
	file_fp = fdopen(fd_tmp, "w"); // 返回 写 模式的 FILE 指针
	fputs("NetWork C programming \n", file_fp);
	free(file_path);
	fclose(file_fp);
	return EXIT_SUCCESS;
}
