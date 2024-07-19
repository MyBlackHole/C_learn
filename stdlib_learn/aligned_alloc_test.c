#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int *p1 = (int *)malloc(10 * sizeof(int));
	printf("default-aligned addr:   %p\n", (void *)p1);
	free(p1);

	// 分配空间的起始地址对齐的位置
	int *p2 = (int *)aligned_alloc(1024, 1024 * sizeof(int));
	printf("1024-byte aligned addr: %p\n", (void *)p2);
	free(p2);
	exit(0);
}
