//
// Created by BlackHole on 2020/7/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 11

int demo_strlcpy_test_main()
{
	char src[] = "hello world";
	char buf[4] = { 0 };
	strlcpy(buf, src, sizeof(buf));
	printf("%sok", buf);
	return EXIT_SUCCESS;
}


// Output:
// ❯ xmake run string_learn strncpy_test
// hellhello worldok%
// ❯ xmake run string_learn strlcpy_test
// helok%
