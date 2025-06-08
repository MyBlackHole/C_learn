//
// Created by BlackHole on 2020/7/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 11

int demo_strncpy_test_main()
{
	char src[] = "hello world";
	char buf[4] = { 0 };
	strncpy(buf, src, sizeof(buf));
	printf("%sok", buf);
	return EXIT_SUCCESS;
}
