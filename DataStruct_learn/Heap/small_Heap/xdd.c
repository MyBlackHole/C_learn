/**
 * @file xdd.c
 * @author {BlackHole} ({1358244533@qq.com})
 * @brief
 * @date 2021/08/18 23:10:17
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "xdd.h"

#include <stdio.h>
#include <stdlib.h>

MinHeap *InitMinHeap(MinHeap *heap, int size)
{
	if (size < 0) {
		printf("size < 0");
		exit(1);
	}

	heap->array = (Node *)malloc(size * sizeof(Node));

	if (!heap->array) {
		printf("(Node *)malloc(size * sizeof(Node))");
		exit(1);
	}

	heap->len = 0;
	heap->MaxSize = size;
	return heap;
}

int EmptyHeap(MinHeap *heap)
{
	return heap->len == 0;
}

int FixUp(MinHeap *heap)
{
	int j = heap->len - 1;
	int f;
	while ((f = ((j - 1) >> 1)) >= 0) {
		/* code */
		if (heap->array[f] <= heap->array[j]) {
			break;
		}

		int tmpe = heap->array[f];
		heap->array[f] = heap->array[j];
		heap->array[j] = tmpe;
		j = f;
	}

	return f;
}

int FixDown(MinHeap *heap)
{
	int f = 0;
	int k;
	while ((k = ((f << 1) + 1)) < heap->len) {
		/* code */
		if (k < heap->len - 1) {
			if (heap->array[k] > heap->array[k + 1]) {
				k++;
			}
		}
		if (heap->array[f] <= heap->array[k]) {
			break;
		}

		int tmpe = heap->array[f];
		heap->array[f] = heap->array[k];
		heap->array[k] = tmpe;
		f = k;
	}
	return f;
}

int InsertHeap(MinHeap *heap, Node node)
{
	if (heap->len == heap->MaxSize) {
		Node *p;
		p = (Node *)realloc(heap->array, heap->MaxSize * 2);
		if (!p) {
			free(heap->array);
			printf("(Node *)realloc(heap->array, heap->MaxSize * 2)");
			exit(1);
		}
		heap->array = p;
		heap->MaxSize = heap->MaxSize * 2;
	}

	heap->array[heap->len++] = node;

	return FixUp(heap);
}

Node DeleteHeap(MinHeap *heap)
{
	if (heap->len <= 0) {
		printf("heap->len <= 0");
		exit(1);
	}
	int value = heap->array[0];
	heap->array[0] = heap->array[--heap->len];
	heap->array[heap->len] = 0;
	FixDown(heap);
	return value;
}

int ClearHeap(MinHeap *heap)
{
	if (heap->array != NULL) {
		free(heap->array);
		heap->len = 0;
		heap->MaxSize = 0;
	}
	return 0;
}
