#include <stdio.h>

#include "./array_queue.h"

int main()
{
	int i = 0;
	int ret = 0;
	int data = 0;
	array_queue *queue = NULL;

	queue = array_queue_create(4);
	if (queue == NULL) {
		printf("\r\n queue is create failed.");
		return 0;
	}

	/*队列时空时，出队返回错误*/
	ret = array_queue_dequeue(queue, &data);
	if (ret != 0) {
		printf("\r\n queue %d dequeue failed.", ret);
	}

	/*队列大小是4，入队5个，最后一个报错*/
	for (i = 0; i < 5; i++) {
		ret = array_queue_enqueue(queue, i);
		if (ret != 0) {
			printf("\r\n queue %d enqueue failed.", i);
		}
	}

	array_queue_dump(queue);

	ret = array_queue_dequeue(queue, &data);
	if (ret != 0) {
		printf("\r\n queue %d dequeue failed.", i);
	}
	printf("\r\n queue %d dequue.", data);
	array_queue_dump(queue);
	data = 5;
	printf("\r\n queue %d enqueue.", data);
	ret = array_queue_enqueue(queue, data);
	if (ret != 0) {
		printf("\r\n queue %d enqueue failed.\n", data);
	}
	array_queue_dump(queue);

	array_queue_destory(queue);
	return 0;
}
