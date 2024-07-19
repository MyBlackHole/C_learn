#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 大写转小写
 */
int demo_tolower_test_main(int argc, char *argv[])
{
	int index;
	char string[] = "BLACK HOLE;";
	printf("%s\n", string);
	for (index = 0; index < strlen(string); index++) {
		putchar(tolower(string[index]));
	}
	printf("\n");
	exit(0);
}
