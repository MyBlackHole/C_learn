#include <stdio.h>
#include <stdlib.h>

int demo_getc_main(void)
{
	int item;
	// 获取stdin流输入字符 回车结束
	while ((item = getc(stdin)) != EOF) {
		// 写入流字符
		if (putc(item, stdout) == EOF) {
			perror("output error");
			exit(1);
		}
	}
	if (ferror(stdin)) {
		perror("input error");
		exit(1);
	}
	exit(0);
}
