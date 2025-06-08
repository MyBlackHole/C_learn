#include <stdio.h>

/* 返回前面引导位0 的个数，如果a=0 的话， 不确定*/
int clz(unsigned int int_tmp)
{
	return __builtin_clz(int_tmp);
}

int demo_builtin_clz_main()
{
	unsigned int int_tmp = 0;
	int_tmp = 0;
	printf("0x%x ret=%d\n", int_tmp, clz(int_tmp));

	int_tmp = 1;
	printf("0x%x ret=%d\n", int_tmp, clz(int_tmp));

	int_tmp = 2;
	printf("0x%x ret=%d\n", int_tmp, clz(int_tmp));

	int_tmp = 4;
	printf("0x%x ret=%d\n", int_tmp, clz(int_tmp));

	int_tmp = 8;
	printf("0x%x ret=%d\n", int_tmp, clz(int_tmp));

	int_tmp = 16;
	printf("0x%x ret=%d\n", int_tmp, clz(int_tmp));
	;

	int_tmp = 0x0FFFFFFF;
	printf("0x%x ret=%d\n", int_tmp, clz(int_tmp));

	int_tmp = 0x1FFFFFFF;
	printf("0x%x ret=%d\n", int_tmp, clz(int_tmp));

	int_tmp = 0x2FFFFFFF;
	printf("0x%x ret=%d\n", int_tmp, clz(int_tmp));

	int_tmp = 0x4FFFFFFF;
	printf("0x%x ret=%d\n", int_tmp, clz(int_tmp));

	int_tmp = 0x8FFFFFFF;
	printf("0x%x ret=%d\n", int_tmp, clz(int_tmp));

	int_tmp = 0xFFFFFFFF;
	printf("0x%x ret=%d\n", int_tmp, clz(int_tmp));

	return 0;
}
