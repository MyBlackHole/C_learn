#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// 判断是不是 gcc
#ifdef __GNUC__

// gcc 连接方式
#define CppConcat(x, y) x y // CppConcat(a.,b) == a. b
#define Concat(x, y) x##y // 连接 Concat(a.,b) == a.b

#else

#endif /* ifdef __GNUC__ */

struct Test {
	int num;
};

typedef struct Test Test;

void test1()
{
	printf("start ## test\n");

	Test t;
	t.num = 100;
	// printf("%d\n", t.num);
	printf("%d\n", CppConcat(t., num));

	printf("end ## test\n");
}

#define BOOTSTRAP

#define CATALOG(x) typedef struct Concat(FormData_, x)

CATALOG(pg_attribute) BOOTSTRAP
{
	char attalign;
}
FormData;

int main(int argc, char *argv[])
{
	test1();
	return EXIT_SUCCESS;
}
