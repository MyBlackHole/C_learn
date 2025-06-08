#include <stdio.h>
#include <stdlib.h>

#define NUM 3

typedef struct {
	int data[2];
} data_t;

static data_t *arr[NUM];

// 指针数组空间分配
static void test()
{
	for (int i = 0; i < NUM; i++) {
		arr[i] = (data_t *)malloc(sizeof(data_t));
		arr[i]->data[0] = i;
		arr[i]->data[1] = i * 2;
		printf("arr[%d]->data[0] = %d, arr[%d]->data[1] = %d\n", i,
		       arr[i]->data[0], i, arr[i]->data[1]);
	}
}

int demo_ptr_arr1_main(int argc, char *argv[])
{
	test();

	exit(EXIT_SUCCESS);
}
