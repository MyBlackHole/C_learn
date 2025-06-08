#include "./list_queue.h"

#include <stdio.h>
#include <stdlib.h>

/*创建队列头*/
list_queue *list_queue_create()
{
	list_queue *queue = NULL;

	queue = (list_queue *)malloc(sizeof(list_queue));
	if (queue == NULL) {
		return NULL;
	}

	queue->num = 0;
	queue->head = NULL;
	queue->tail = NULL;

	return queue;
}

void list_queue_destroy(list_queue *queue)
{
	int i = 0;
	int data = 0;

	if ((queue == NULL) || (list_queue_is_empty(queue))) {
		return;
	}

	while (!list_queue_is_empty(queue)) {
		(void)list_queue_dequeue(queue, &data);
	}

	free(queue);
	return;
}

int list_queue_enqueue(list_queue *queue, int data)
{
	queue_node *ptmp = NULL;

	if (queue == NULL) {
		return -1;
	}

	ptmp = (queue_node *)malloc(sizeof(queue_node));
	if (ptmp == NULL) {
		return -1;
	}

	ptmp->data = data;
	ptmp->next = NULL;
	if (queue->head == NULL) {
		queue->head = ptmp;
	} else {
		queue->tail->next = ptmp;
	}
	queue->tail = ptmp;
	queue->num++;

	return 0;
}

/*出队*/
int list_queue_dequeue(list_queue *queue, int *data)
{
	queue_node *ptmp = NULL;

	if ((queue == NULL) || (data == NULL) || list_queue_is_empty(queue)) {
		return -1;
	}

	*data = queue->head->data;
	ptmp = queue->head;
	queue->head = queue->head->next;
	queue->num--;

	if (queue->head == NULL) {
		queue->tail = NULL;
	}

	free(ptmp);
	return 0;
}

void list_queue_dump(list_queue *queue)
{
	int i = 0;
	queue_node *ptmp = NULL;

	if ((queue == NULL) || (list_queue_is_empty(queue))) {
		return;
	}

	ptmp = queue->head;

	printf("\r\n----dump queue num = %d--------", queue->num);
	while (ptmp != NULL) {
		printf("\r\nnode[%d] = %d", i, ptmp->data);
		i++;
		ptmp = ptmp->next;
	}
	printf("\r\n---------------------------------\r\n");

	return;
}
