#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/queue.h>

typedef struct num_node /* 链表节点结构体 */
{
	SLIST_ENTRY(num_node) field;
	uint32_t num;
} num_node;

typedef SLIST_HEAD(num_head, num_node) num_head; /* 链表头结构体 */

/* 合并两个链表 */
static num_node *merge(num_node *node1, num_node *node2)
{
	if (node1 == NULL) {
		return node2;
	}
	if (node2 == NULL) {
		return node1;
	}

	num_node *res, *ptr;

	if (node1->num < node2->num) {
		res = node1;
		node1 = SLIST_NEXT(node1, field);
	} else {
		res = node2;
		node2 = SLIST_NEXT(node2, field);
	}

	ptr = res;

	while (node1 != NULL && node2 != NULL) {
		if (node1->num < node2->num) {
			SLIST_NEXT(ptr, field) = node1;
			node1 = SLIST_NEXT(node1, field);
		} else {
			SLIST_NEXT(ptr, field) = node2;
			node2 = SLIST_NEXT(node2, field);
		}
		ptr = SLIST_NEXT(ptr, field);
	}

	if (node1 != NULL) {
		SLIST_NEXT(ptr, field) = node1;
	} else if (node2 != NULL) {
		SLIST_NEXT(ptr, field) = node2;
	}

	return res;
}

/* 对链表节点进行归并排序 */
static num_node *mergeSort(num_node *node)
{
	if (node == NULL || SLIST_NEXT(node, field) == NULL) {
		return node;
	}

	num_node *fast = node;
	num_node *slow = node;
	while (SLIST_NEXT(fast, field) != NULL) {
		if (SLIST_NEXT(SLIST_NEXT(fast, field), field) == NULL) {
			break;
		}
		fast = SLIST_NEXT(SLIST_NEXT(fast, field), field);
		slow = SLIST_NEXT(slow, field);
	}

	fast = slow;
	slow = SLIST_NEXT(slow, field);
	SLIST_NEXT(fast, field) = NULL;
	fast = mergeSort(node);
	slow = mergeSort(slow);
	return merge(fast, slow);
}

/* 对链表头进行归并排序 */
void num_mergeSort(num_head *head)
{
	SLIST_FIRST(head) = mergeSort(SLIST_FIRST(head));
}

int demo_SLIST_ENTRY_main(void)
{
	/* 从堆空间申请链表表头并初始化 */
	num_head *p_head = malloc(sizeof(num_head));
	SLIST_INIT(p_head);

	/* 为链表添加10个0~100的随机数 */
	num_node *elm;
	for (int i = 0; i < 10; ++i) {
		elm = malloc(sizeof(num_node));
		elm->num = rand() % 100;
		SLIST_INSERT_HEAD(p_head, elm, field);
	}

	/* 打印排序前的链表 */
	printf("Before sort:\n");
	SLIST_FOREACH(elm, p_head, field)
	{
		printf("addr = %p, num = %d\n", elm, elm->num);
	}

	/* 归并排序函数 */
	num_mergeSort(p_head);

	/* 打印排序后的链表 */
	printf("After sort:\n");
	SLIST_FOREACH(elm, p_head, field)
	{
		printf("addr = %p, num = %d\n", elm, elm->num);
	}

	/* 销毁链表释放空间 */
	while (!SLIST_EMPTY(p_head)) {
		num_node *ptr = SLIST_FIRST(p_head);
		SLIST_REMOVE_HEAD(p_head, field);
		free(ptr);
	}
	free(p_head);

	return EXIT_SUCCESS;
}
