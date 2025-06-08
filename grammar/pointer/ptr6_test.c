/*
 * 指针测试
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int a;
	char b;
	short c;
	long d;
} my_struct;

my_struct my_ptr[3];

int demo_ptr6_main(int argc, char *argv[])
{
	my_struct *p1 = my_ptr;
	p1->a = 10;
	p1->b = 'a';
	my_struct *p2 = my_ptr + 1;
	p2->a = 20;
	p2->b = 'b';
	printf("my_ptr[0].a = %d, my_ptr[0].b = %c\n", my_ptr[0].a,
	       my_ptr[0].b);
	printf("my_ptr[1].a = %d, my_ptr[1].b = %c\n", my_ptr[1].a,
	       my_ptr[1].b);

	void *p3 = (uint64_t *)my_ptr + 1;
	void *p4 = ((uint64_t *)my_ptr) + 1;
	void *p5 = (uint64_t *)(my_ptr + 1);
	printf("my_ptr = %p, p3 = %p, p4 = %p, p5 = %p\n", my_ptr, p3, p4, p5);
	my_struct *p6 = (my_struct *)(p5);

	printf("p6->a = %d, p6->b = %c\n", p6->a, p6->b);

	my_struct *p7 = (my_struct *)(p3);
	printf("p7->a = %d, p7->b = %c\n", p7->a, p7->b);

	printf("sizeof(my_struct) = %lu\n", sizeof(my_struct));
	return EXIT_SUCCESS;
}
