#include <stdio.h>
#include <stdlib.h>

int demo_getchar_main(void)
{
	int item;

	while ((item = getchar()) != EOF) {
		putchar(item);
	}
	return EXIT_SUCCESS;
}
