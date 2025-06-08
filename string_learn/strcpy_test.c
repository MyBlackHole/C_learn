//
// Created by BlackHole on 2020/7/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int msg();

int demo_strcpy_test_main(int argc, char **argv)
{
	//    int val;
	//    char str[20];
	//
	//    strcpy(str, "98993489");
	////  atoi 字符串->整型值
	//    val = atoi(str);
	//    printf("字符串值 = %s, 整型值 = %d\n", str, val);
	//
	//    strcpy(str, "runoob.com");
	//    val = atoi(str);
	//    printf("字符串值 = %s, 整型值 = %d\n", str, val);
	msg();
	return (0);
}

// msg

typedef struct {
	int number;
	char *msg;
} unit_t;

int msg()
{
	unit_t *ptr = malloc(sizeof(unit_t));
	if (ptr == NULL) {
		printf("out of memory\n");
		exit(1);
	}
	ptr->number = 3;
	ptr->msg = malloc(50);
	strcpy(ptr->msg, "Hello world!");
	printf("number: %d\nmsg: %s\n", ptr->number, ptr->msg);
	free(ptr->msg);
	free(ptr);
	ptr = NULL;
	printf("%ld, int:%ld", sizeof(unit_t), sizeof(NULL));
	return EXIT_SUCCESS;
}
