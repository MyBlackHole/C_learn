#include <stdio.h>

#define PYL(type, member) ((unsigned long long)&((struct type *)0)->member)

struct Test {
	int a;
	int b;
};

int main()
{
	struct Test test = {};
	struct Test *p;
	p = &test;
	(void)p;
	printf("000\n");
	// printf("%d\n", test.a);
	// printf("%d\n", &(test).a);
	// printf("%d\n", p->a);
	// printf("%d\n", (&(test))->a);
	// printf("%d\n", &(test));
	// printf("%p\n", &(test.b));
	printf("%p\n", &((struct Test *)0)->b);
	// printf("%p\n", PYL(Test, b));
	printf("%lld\n", PYL(Test, b));
	// printf("%p\n", 0);

	// printf("%ld\n", (unsigned long long)&(struct Test *)0);
	return 0;
}
