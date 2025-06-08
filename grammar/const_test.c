#include <stdio.h>
#include <stdlib.h>

int demo_const_main(int argc, char *argv[])
{
	int const num = 1;
	// const int num = 1;
	// num = 3;
	int *num_p = (int *)&num;
	*num_p = 2;
	printf("num = %d\n", num);
	printf("p = %p\n", num_p);

	return EXIT_SUCCESS;
}
