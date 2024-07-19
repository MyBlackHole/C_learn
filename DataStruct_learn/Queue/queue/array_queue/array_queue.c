#include "./array_queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

array_queue *array_queue_create(int size)
{
	array_queue *queue = NULL;

	queue = (array_queue *)malloc(sizeof(array_queue));
	if (queue == NULL) {
		return NULL;
	}
	queue->array = (int *)malloc(sizeof(int) * size);
	if (queue->array == NULL) {
		free(queue);
		return NULL;
	}
	queue->size = size;
	queue->num = 0;
	queue->head = 0;
	queue->tail = 0;

	return queue;
}

void array_queue_destory(array_queue *queue)
{
	if (queue == NULL) {
		return;
	}

	if (queue->array != NULL) {
		free(queue->array);
	}

	free(queue);
	return;
}

/*入队列 */
int array_queue_enqueue(array_queue *queue, int data)
{
	/*队列为空，或者队列满时，返回-1*/
	if ((queue == NULL) || (array_queue_is_full(queue))) {
		return -1;
	}

	queue->num++;
	queue->array[queue->tail] = data;
	queue->tail = (queue->tail + 1) % queue->size;

	return 0;
}

/*出队列*/
int array_queue_dequeue(array_queue *queue, int *data)
{
	/*队列为空，数据存储为空，队列为空时返回-1*/
	if ((queue == NULL) || (data == NULL) ||
	    (array_queue_is_empty(queue))) {
		return -1;
	}
	*data = queue->array[queue->head];
	queue->num--;
	queue->head = (queue->head + 1) % queue->size;

	return 0;
}

void array_queue_dump(array_queue *queue)
{
	int i = 0;
	int pos = 0;

	if ((queue == NULL) || (array_queue_is_empty(queue))) {
		printf("\r\n queue is empty");
		return;
	}

	printf("\r\n size:%d,num:%d,head:%d,tali:%d", queue->size, queue->num,
	       queue->head, queue->tail);
	for (i = 0; i < queue->num; i++) {
		pos = (queue->head + i) % queue->size;
		printf("\r\n array[%d] = %d", pos, queue->array[pos]);
	}
	return;
}
