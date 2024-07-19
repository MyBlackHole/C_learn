#include <stdio.h>
#include <stdlib.h>

void test()
{
	static int j_1;
	printf("%d\n", j_1++);
}

int demo_static_main(int argc, char *argv[])
{
	for (int i = 0; i < 5; i++) {
		test();
	}
	return 0;
}
