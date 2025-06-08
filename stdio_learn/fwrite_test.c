#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int demo_fwrite_main(int argc, char *argv[])
{
	FILE *fp_tmp;
	char str[] = "This is runoob.com";
	char *name = "/file.txt";
	char *path = dirname(argv[0]);
	char *file_path = malloc(strlen(name) + strlen(path));
	strcpy(file_path, path);
	// 多加一个空格
	strncat(file_path, name, strlen(name) + 1);

	printf("%s\n", file_path);
	fp_tmp = fopen(file_path, "w");
	fwrite(str, sizeof(str), 1, fp_tmp);

	fclose(fp_tmp);

	free(file_path);

	return (0);
}
