#include <stdio.h>

inline int test_1();

int demo_FUNCTION_main()
{
	test_1();
	return 0;
}

int test_1()
{
	printf("%s\n", __FUNCTION__);
	return 0;
}
