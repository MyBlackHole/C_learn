#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int demo_free_1_main(int argc, char **argv)
{
	char *p = malloc(40);
	// char *p2 = NULL;
	// char *p3 = NULL;
	if (p == NULL) {
		printf("out of memory\n");
		exit(1);
	}
	// p3 = p;
	// p2 = p3;
	printf("allocated %d bytes at %p\n", 40, p);
	free(p);
	printf("freed 1n\n");
	// free(p2);
	// printf("freed 2\n");
	return 0;
}
