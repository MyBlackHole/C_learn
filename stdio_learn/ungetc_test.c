#include <stdlib.h>
#include <stdio.h>

#define NUM 256

int demo_ungetc_main()
{
	FILE *fp_tmp;
	int item;
	char buffer[NUM];

	fp_tmp = fopen("file.txt", "r");
	if (fp_tmp == NULL) {
		perror("打开文件时发生错误");
		return (-1);
	}
	while (!feof(fp_tmp)) {
		item = getc(fp_tmp);
		/* 把 ! 替换为 + */
		if (item == '!') {
			ungetc('+', fp_tmp);
		} else {
			ungetc(item, fp_tmp);
		}
		fgets(buffer, NUM, fp_tmp);
		fputs(buffer, stdout);
	}
	return EXIT_SUCCESS;
}
