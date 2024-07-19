#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// #define offsetof(type, member) (int)(&((type *)0)->member)

// // 偏移量
// #define offsetof(type, member) __builtin_offsetof(type, member)

typedef struct test {
	char i;
	int j;
	char k;
} test_t;
//
int main(int argc, char *argv[])
{
	test_t *ptr = malloc(sizeof(test_t));
	ptr->j = 100;
	printf("%ld -- %p -- %d\n", offsetof(test_t, j), ptr,
	       *(int *)((size_t)ptr + offsetof(test_t, j)));
	return EXIT_SUCCESS;
}
