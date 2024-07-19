#include <stdio.h>

struct A {
	int a;
	int b;
};

int demo_struct_main()
{
	struct A a_1 = { .a = 2, .b = 3 };
	printf("a1.a--%d\n", a_1.a);

	struct A a_2 = { .a = 3, .b = 4 };
	printf("a2.a--%d\n", a_2.a);
	return 0;
}
