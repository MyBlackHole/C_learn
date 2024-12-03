#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUM 15

int demo_strncmp_3_main(int argc, char *argv[])
{
	int ret;
	if (argc < 3) {
		printf("Usage: %s str1 str2\n", argv[0]);
		return (1);
	}
	ret = strncmp(argv[1], argv[2], strlen(argv[1]));
	if (ret < 0) {
		printf("str1 小于 str2");
	} else if (ret > 0) {
		printf("str1 大于 str2");
	} else {
		printf("str1 等于 str2");
	}

	return EXIT_SUCCESS;
}

// output:
// 
// ❯ xmake run string_learn strncmp_3 /aa /aaa
// str1 等于 str2%
// ❯ xmake run string_learn strncmp_3 /aaaa /aaa
// str1 大于 str2%
