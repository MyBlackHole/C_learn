#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int demo_memcpy_1_main()
{
	void *ptr_dest = NULL;
	void *ptr_src = NULL;
	int size = 0;
	int dest_size = 0;
	int src_size = 0;

	scanf("%d %d %d", &size, &dest_size, &src_size);
	printf("size = %d, dest_size = %d, src_size = %d\n", size, dest_size,
	       src_size);

	ptr_dest = malloc(dest_size);
	if (ptr_dest == NULL) {
		printf("Memory allocation failed");
		goto error__;
	}

	ptr_src = malloc(src_size);
	if (ptr_src == NULL) {
		printf("Memory allocation failed");
		goto ptr_dest_free;
	}

	strcpy(ptr_src, "Hello World");

	memcpy(ptr_dest, ptr_src, size);
	printf("%s", (char *)ptr_dest);
	return EXIT_SUCCESS;

	free(ptr_src);
ptr_dest_free:
	free(ptr_dest);
error__:
	return EXIT_FAILURE;
}

// output:
//
// ❯ xmake run string_learn memcpy_1
// 10 20 10
// size = 10, dest_size = 20, src_size = 10
// Hello Worl%
// ❯ xmake run string_learn memcpy_1
// 20 20 10
// size = 20, dest_size = 20, src_size = 10
// Hello World%
