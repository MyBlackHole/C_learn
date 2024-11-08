#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *str;
void *my_malloc(size_t size)
{
	void *ptr = malloc(size);
	if (ptr == NULL) {
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	printf("Allocated %lu bytes at %p\n", size, ptr);
	return ptr;
}

int test_malloc()
{
	str = (char *)my_malloc(0x4100000);
	printf("str: %p\n", str);
	return 0;
}

int demo_malloc_1_main()
{
	test_malloc();
	test_malloc();
	free(str);
	return (0);
}

// output: (static 会保证 malloc 一次)
//
// ❯ xmake run stdlib_learn malloc_1
// Allocated 68157440 bytes at 0x7b012c200010
// str: 0x7b012c200010
// Allocated 68157440 bytes at 0x7b0128000010
// str: 0x7b0128000010
