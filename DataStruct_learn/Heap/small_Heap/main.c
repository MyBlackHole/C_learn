/**
 * @file test_xdd.c
 * @author {BlackHole} ({1358244533@qq.com})
 * @brief
 * @date 2021/08/19 00:26:01
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>

#include "xdd.h"

int main(int argc, char *argv[])
{
	int i, x;
	int a[8] = { 23, 56, 40, 62, 38, 55, 10, 16 };
	MinHeap mh;
	InitMinHeap(&mh, 5);
	for (i = 0; i < 8; i++) {
		InsertHeap(&mh, a[i]);
		printf("%d\n", mh.array[i]);
	}
	// 依次删除堆顶元素并显示出来，直到堆空为止
	while (!EmptyHeap(&mh)) {
		x = DeleteHeap(&mh);
		printf("%d", x);
		if (!EmptyHeap(&mh)) {
			printf(",");
		}
	}
	printf("\n");
	ClearHeap(&mh);
	return 0;
}
