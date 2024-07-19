// Queue ADT implementation ... COMP2521

#include "queue.h"

#include <assert.h>
#include <stdlib.h>

typedef struct node {
	int data;
	// 链表
	struct node *next;
} NodeT;

typedef struct QueueRep {
	int length;
	// 头部
	NodeT *head;
	// 尾部
	NodeT *tail;
} QueueRep;

// set up empty queue
queue newQueue()
{
	queue Q = malloc(sizeof(QueueRep));
	Q->length = 0;
	Q->head = NULL;
	Q->tail = NULL;
	return Q;
}

// remove unwanted queue
// 销毁队列
void dropQueue(queue Q)
{
	NodeT *curr = Q->head;
	while (curr != NULL) {
		NodeT *temp = curr->next;
		free(curr);
		curr = temp;
	}
	free(Q);
}

// check whether queue is empty
// 是否空队列
int QueueIsEmpty(queue Q)
{
	return (Q->length == 0);
}

// insert an int at end of queue
// 添加节点
void QueueEnqueue(queue Q, int v)
{
	NodeT *new = malloc(sizeof(NodeT));
	assert(new != NULL);
	new->data = v;
	new->next = NULL;
	if (Q->tail != NULL) {
		// 非首次添加
		Q->tail->next = new;
		Q->tail = new;
	} else {
		// 首次添加
		Q->head = new;
		Q->tail = new;
	}
	Q->length++;
}

// remove int from front of queue
// 从头部弹出一个元素
int QueueDequeue(queue Q)
{
	assert(Q->length > 0);
	NodeT *p = Q->head;
	Q->head = Q->head->next;
	if (Q->head == NULL) {
		Q->tail = NULL;
	}
	Q->length--;
	int d = p->data;
	free(p);
	return d;
}
