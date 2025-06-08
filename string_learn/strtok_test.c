#include <stdio.h>
#include <string.h>

int demo_strtok_test_main()
{
	char str[80] = "This is - www.runoob.com - website";
	// 分割符号
	const char separator[2] = "-";
	char *token;

	/* 根据分割符获取第一个子字符串 */
	token = strtok(str, separator);

	/* 继续获取其他的子字符串 */
	while (token != NULL) {
		printf("%s\n", token);

		token = strtok(NULL, separator);
	}

	return (0);
}
