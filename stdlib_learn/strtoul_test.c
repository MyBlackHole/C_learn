#include <stdio.h>
#include <stdlib.h>

int main()
{
	char buffer[256];
	unsigned long ul;
	printf("Enter an unsigned number: ");
	// 读取字符串到 buffer
	fgets(buffer, 256, stdin);
	ul = strtoul(buffer, NULL, 0);
	printf("Value entered: %lu.\n", ul);
	return 0;
}
