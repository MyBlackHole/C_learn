/**
* @file main1.c
* @author {BlackHole} ({1358244533@qq.com})
* @brief
* @date 2021/08/18 23:20:09
*
* @copyright Copyright (c) 2021
*
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("%d\n", 1 == 0);
	int *i;
	i = (int *)malloc(10 * sizeof(int));
	printf("%d\n", i[0]);
	return 0;
}