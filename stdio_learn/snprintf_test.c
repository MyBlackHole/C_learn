#include <stdio.h>
#include <stdlib.h>

#define NUM 50

int demo_snprintf_main()
{
	char buffer[NUM];
	char *string = "runoobcom black hole";
	int int1 = 1111112;
	int buf = 0;
	char port[NUM];

	// 读取字符串并存储在 buffer 中
	int ret = snprintf(buffer, NUM, "%s\n", string);

	// 输出 buffer及字符数
	printf("string:\n%s\ncharacter count = %d\n", buffer, ret);

	// 读取字符串并存储在 buffer 中
	buf = snprintf(port, 10, "%d\n", int1);

	// 输出 buffer及字符数
	printf("string:\n%s\ncharacter count = %d\n", port, buf);
	exit(0);
}
