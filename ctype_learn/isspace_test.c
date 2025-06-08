#include <ctype.h>
#include <stdio.h>

/* 返回值为非零（真）表示c是空白符，返回值为零（假）表示c不是空白符 */
/*
 *  空白符
 *  ' ', '\t', '\v', '\f', '\r'
 */

void func1()
{
	char value;
	int index = 0;
	char str[] = "Example sentence to test isspace\n";
	while (str[index]) {
		value = str[index];
		if (isspace(value)) {
			value = '\n';
		}
		putchar(value);
		index++;
	}
}

int demo_isspace_test_main()
{
	func1();
	return 0;
}
