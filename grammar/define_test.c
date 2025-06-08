#include <stdio.h>
#include <stdlib.h>

#if 0
#define MAX(i, j) ((i) > (j) ? (i) : (j))
#else
#define MAX(i, j) ({ (i) > (j) ? (i) : (j); })
int max(int a__, int b__)
{
	return a__ > b__ ? a__ : b__;
}
#endif

int demo_define_main(int argc, char *argv[])
{
	int i_1 = 5;
	int j_1 = 3;

	printf("i = %d\tj = %d\n", i_1, j_1);
	printf("%d\n", MAX(i_1++, j_1++));
	printf("i = %d\tj = %d\n", i_1, j_1);
	exit(0);
}
