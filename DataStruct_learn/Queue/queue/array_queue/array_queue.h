#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

typedef struct _array_queue {
	int size; /*队列的大小*/
	int num; /*当前存储数据的大小*/
	int head; /*队列的头*/
	int tail; /*队列的尾*/
	int *array; /*数据存储区*/
} array_queue;

#define array_queue_is_empty(array_queue) (array_queue->num == 0)
#define array_queue_is_full(array_queue) \
	((array_queue->num) == (array_queue->size))

extern array_queue *array_queue_create(int size);
extern void array_queue_destory(array_queue *queue);
/*入队列 */
extern int array_queue_enqueue(array_queue *queue, int data);
/*出队列*/
extern int array_queue_dequeue(array_queue *queue, int *data);

extern void array_queue_dump(array_queue *queue);

#endif
