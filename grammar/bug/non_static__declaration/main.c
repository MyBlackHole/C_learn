#include <stdio.h>
#include <stdlib.h>

#include "test.h"

int main(void)
{
	int ret;
	ret = add(1, 2);
	printf("%d\n", ret);

	return EXIT_SUCCESS;
}
