#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int demo_feof_main(int args, char **argv)
{
	FILE *fp_tmp;
	int item;

	char *path = dirname(argv[0]);
	char *filename = "/file.txt";
	char *name = malloc(strlen(path) + strlen(filename));

	strcpy(name, path);
	strcat(name, filename);

	fp_tmp = fopen(name, "r");
	if (fp_tmp == NULL) {
		printf("打开文件 file:[%s] 时发生错误", name);
		return (-1);
	}
	while (1) {
		item = fgetc(fp_tmp);
		if (feof(fp_tmp)) {
			break;
		}
		printf("%c", item);
	}
	fclose(fp_tmp);
	return (0);
}
