#include <assert.h>
#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

// 定义异常码和上下文环境
static sigjmp_buf exception_env;
volatile int exception_code; // 必须声明为 volatile

// 宏定义：TRY-CATCH 结构
#define TRY                                           \
	exception_code = sigsetjmp(exception_env, 1); \
	if (exception_code == 0)

#define CATCH else

#define THROW(code) siglongjmp(exception_env, code)

// 示例函数：可能抛出异常的操作
void risky_operation(int condition)
{
	if (condition) {
		printf("Error occurred! Throwing exception...\n");
		THROW(42); // 抛出异常码 42
	}
	printf("Operation successful.\n");
}

int demo_try_catch_main()
{
	TRY
	{
		printf("Attempting risky operation...\n");
		risky_operation(1); // 传入 1 触发异常
	}
	CATCH
	{
		switch (exception_code) {
		case 42:
			printf("Caught exception 42: Invalid condition.\n");
			break;
		default:
			printf("Unknown exception: %d\n", exception_code);
		}
	}

	return EXIT_SUCCESS;
}
