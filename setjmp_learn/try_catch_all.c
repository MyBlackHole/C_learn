#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>

static sigjmp_buf abort_env; // 保存跳转上下文
volatile sig_atomic_t abort_flag; // 原子类型，用于信号处理

// 自定义 SIGABRT 处理函数
void handle_abort(int sig)
{
	if (sig == SIGABRT) {
		// 跳转回 TRY 的 sigsetjmp 点，并传递错误码
		siglongjmp(abort_env, 1);
	}
	if (sig == SIGSEGV) {
		// 跳转回 TRY 的 sigsetjmp 点，并传递错误码
		siglongjmp(abort_env, 2);
	}
}

// 定义 TRY-CATCH 宏
#define TRY                                               \
	signal(SIGABRT, handle_abort); /* 注册信号处理 */ \
	signal(SIGSEGV, handle_abort); /* 注册信号处理 */ \
	if (sigsetjmp(abort_env, 1) == 0) /* 保存上下文 */

#define CATCH else

// 示例：触发 abort() 的函数
void risky_function()
{
	printf("About to abort...\n");
	abort(); // 触发 SIGABRT
}

int demo_try_catch_all_main()
{
	TRY
	{
		risky_function();
		printf("This line will not be executed.\n");
	}
	CATCH
	{
		printf("Caught SIGABRT! Performing cleanup...\n");
	}

	return 0;
}
