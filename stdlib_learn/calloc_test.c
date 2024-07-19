#include <stdio.h>
#include <stdlib.h>

/* C 库函数 void *calloc(size_t nitems, size_t size) 分配所需的
 * 存空间，并返回一个指向它的指针。malloc 和 calloc
 * 之间的不同点是，malloc 不会设置内存为零，而 calloc 会设置分配的内存为零。 */
/* void *calloc(size_t nitems, size_t size) */
/* nitems -- 要被分配的元素个数。 */
/* size -- 元素的大小。 */

int main()
{
	int i, n;
	int *a;

	printf("要输入的元素个数：");
	scanf("%d", &n);

	a = (int *)calloc(n, sizeof(int));
	printf("输入 %d 个数字：\n", n);
	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	printf("输入的数字为：");
	for (i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	free(a); // 释放内存
	return (0);
}
