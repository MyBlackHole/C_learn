//
// Created by BlackHole on 2020/8/1.
//

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

// 定义堆的顺序存储类型
struct HeapSq {
	// 定义指向动态数组空间的指针
	ElemType *heap;
	// 定义保存堆长度的变量,即数组长度，数组下标从0开始
	int len;
	// 用于保存初始化时所给的动态数组空间的大小
	int MaxSize;
};

// 1、初始化堆
void InitHeap(struct HeapSq *HBT, int MS)
{
	if (MS <= 0) {
		printf("数组长度参数不合适，需重新给定！\n");
		exit(1);
	}
	HBT->heap = (ElemType *)malloc(MS * sizeof(ElemType));
	if (!HBT->heap) {
		printf("用于动态分配的内存空间用完，退出运行！\n");
		exit(1);
	}
	HBT->MaxSize = MS;
	HBT->len = 0;
}

// 2、清除堆
void ClearHeap(struct HeapSq *HBT)
{
	if (HBT->heap != NULL) {
		free(HBT->heap);
		HBT->len = 0;
		HBT->MaxSize = 0;
	}
}

// 3、检查一个堆是否为空
int EmptyHeap(struct HeapSq *HBT)
{
	if (HBT->len == 0) {
		return 1;
	} else {
		return 0;
	}
}

// 4、向堆中插入一个元素
void InsertHeap(struct HeapSq *HBT, ElemType item)
{
	int index;
	// 若堆满，将数组空间扩展为原来的2倍
	if (HBT->len == HBT->MaxSize) {
		ElemType *p;
		p = (ElemType *)realloc(HBT->heap,
					2 * HBT->MaxSize * sizeof(ElemType));
		if (!p) {
			printf("存储空间用完！\n");
			exit(1);
		}
		printf("存储空间已扩展为原来的2倍！\n");
		HBT->heap = p;
		HBT->MaxSize = 2 * HBT->MaxSize;
	}

	// 向堆尾添加新元素
	HBT->heap[HBT->len] = item;
	// 堆长度加1
	HBT->len++;
	// i指向待调整元素的位置，即其数组下标，初始指向新元素所在的堆尾位置
	index = HBT->len - 1;
	while (index != 0) {
		// j指向下标为i的元素的双亲
		int j = (index - 1) / 2;
		if (item >= HBT->heap[j]) {
			// 若新元素大于待调整元素的双亲，则比较调整结束，退出循环
			break;
		}
		// 将双亲元素下移到待调整元素的位置
		HBT->heap[index] = HBT->heap[j];
		// 使待调整位置变为其双亲位置，进行下一次循环
		index = j;
	}
	// 把新元素调整到最终位置
	HBT->heap[index] = item;
}

// 5、从堆中删除堆顶元素并返回
ElemType DeleteHeap(struct HeapSq *HBT)
{
	ElemType temp, x;
	int index, j;
	if (HBT->len == 0) {
		printf("堆已空，退出运行！\n");
		exit(1);
	}
	// 暂存堆顶元素
	temp = HBT->heap[0];
	HBT->len--;
	if (HBT->len == 0) {
		// 若删除操作后堆为空则返回
		return temp;
	}
	// 将待调整的原堆尾元素暂存x中，以便放入最终位置
	x = HBT->heap[HBT->len];
	// 用i指向待调整元素的位置，初始指向堆顶位置
	index = 0;
	// 用j指向i的左孩子位置，初始指向下标为1的位置
	j = 2 * index + 1;
	// 寻找待调整元素的最终位置，每次使孩子元素上移一层，调整到孩子为空时止
	while (j <= HBT->len - 1) {
		if (j < HBT->len - 1 && HBT->heap[j] > HBT->heap[j + 1]) {
			// 若存在右孩子且较小，使j指向右孩子
			j++;
		}
		if (x <= HBT->heap[j]) {
			// 若x比其较小的孩子还小，则调整结束，退出循环
			break;
		}
		// 否则，将孩子元素移到双亲位置
		HBT->heap[index] = HBT->heap[j];
		// 将待调整位置变为其较小的孩子位置
		index = j;
		// 将j变为新的待调整位置的左孩子位置，继续下一次循环
		j = 2 * index + 1;
	}
	// 把x放到最终位置
	HBT->heap[index] = x;
	// 返回原堆顶元素
	return temp;
}

// 主函数
int main()
{
	int i, x;
	int a[8] = { 23, 56, 40, 62, 38, 55, 10, 16 };
	struct HeapSq b;
	InitHeap(&b, 5);
	for (i = 0; i < 8; i++) {
		InsertHeap(&b, a[i]);
	}
	// 依次删除堆顶元素并显示出来，直到堆空为止
	while (!EmptyHeap(&b)) {
		x = DeleteHeap(&b);
		printf("%d", x);
		if (!EmptyHeap(&b)) {
			printf(",");
		}
	}
	printf("\n");
	ClearHeap(&b);
}
