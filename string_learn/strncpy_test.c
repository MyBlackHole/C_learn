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
	char buf[NUM];
	char src[] = "hello world";
	strncpy(buf, src, sizeof(buf));
	printf("%sok", buf);
	return EXIT_SUCCESS;
}
