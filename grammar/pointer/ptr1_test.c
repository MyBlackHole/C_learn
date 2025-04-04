#include <stdlib.h>

// 防止修改指针指向的内容
void StringCopy(const char *strDestination, const char *strSource);

// 防止修改指针指向的地址
void swap(int *const num_x, double *const num_y);

int demo_ptr1_main(int argc, char *argv[])
{
	// 常量指针
	//
	// 1:
	// 常量指针说的是不能通过这个指针改变变量的值
	// 但是还是可以通过其他的引用来改变变量的值的
	//
	// p_num1 所占用内存的值指向的 int 内存不允许改变
	int num1 = 5;
	const int *p_num1 = &num1;
	(void)p_num1;
	num1 = 6;
	// 可以
	p_num1 = (int *)1;
	// // 不可以
	// *p_num1 = 1;

	// 2:
	// 常量指针指向的值不能改变
	// 但是这并不是意味着指针本身不能改变
	// 常量指针可以指向其他的地址
	int num2 = 5;
	int num3 = 6;
	const int *p_num2 = &num2;
	// 可以
	p_num2 = &num3;
	(void)p_num2;

	// 指针常量
	//
	// 1:
	// 是指指针本身是个常量，不能在指向其他的地址
	// p_p_num4 所占用的内存不允许改变
	int num4 = 5;
	int *p_num4 = &num4;
	int *const p_p_num4 = &num4;
	*p_num4 = 8;
	// 可以
	*p_p_num4 = num4;
	// // 不可以
	// p_p_num4 = &num4;

	// // 指向常量的常指针
	// const int* const p;
	return EXIT_SUCCESS;
}
