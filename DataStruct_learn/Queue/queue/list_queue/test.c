#include <stdio.h>

#include "./list_queue.h"

int main()
{
	int i = 0;
	int data = 0;
	int ret = 0;
	list_queue *queue = NULL;

	queue = list_queue_create();
	if (queue == NULL) {
		printf("\r\nlist queue create falied..");
		return 0;
	}

	for (i = 0; i < 5; i++) {
		(void)list_queue_enqueue(queue, i);
	}
	list_queue_dump(queue);

	ret = list_queue_dequeue(queue, &data);
	if (ret != 0) {
		printf("\r\nlist queue dequeue %d falied.", data);
	}
	printf("\r\nlist queue dequeue %d", data);
	list_queue_dump(queue);

	ret = list_queue_dequeue(queue, &data);
	if (ret != 0) {
		printf("\r\nlist queue dequeue %d failed.", data);
	}
	printf("\r\nlist queue dequeue %d", data);
	list_queue_dump(queue);

	printf("\r\nlist queue enqueue %d", data);
	(void)list_queue_enqueue(queue, data);
	list_queue_dump(queue);

	list_queue_destroy(queue);
	return 0;
}
