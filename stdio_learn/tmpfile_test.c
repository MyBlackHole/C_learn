#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 10

int demo_tmpfile_main(void)
{
	char name[L_tmpnam];
	char line[MAXLINE];
	FILE *fp_tmp;
	printf("%s \n", tmpnam(NULL));
	tmpnam(name);
	printf("%s\n", name);
	fp_tmp = tmpfile();
	if (fp_tmp == NULL) {
		perror("tmpfile error");
	}
	fputs("one line of output \n", fp_tmp);
	// // 设置光标到开头
	// rewind(fp_tmp);
	fseek(fp_tmp, 0L, SEEK_SET);
	if (fgets(line, sizeof(line), fp_tmp) == NULL) {
		perror("fgets error");
	}
	fputs(line, stdout); // print the line we wrote
	exit(EXIT_SUCCESS);
}
// 每次产生不同的临时文件，但是临时文件对我们来说是不可兼得的，所以说是不安全的，对于ISO
// 从规范来说 ，建议使用它更安全的mkstemp函数。
