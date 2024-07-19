#include "test.h"

#include <stdio.h>

void __attribute__((weak)) print(void)
{
	printf("%s\n", "test");
	return;
}

void Test(void)
{
	print();
	return;
}
