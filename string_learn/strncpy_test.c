//
// Created by BlackHole on 2020/7/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 11

int demo_strncpy_test_main()
{
	////    strcpy
	//    char buf[10];
	//    strcpy(buf, "hello");
	//    printf("%sok", buf);

	//    strncpy
	char src[] = "hello world";
	char *buf = malloc(strlen(src) + 1);
	strncpy(buf, src, strlen(src) + 1);
	printf("%sok", buf);
	free(buf);
	return EXIT_SUCCESS;
}
