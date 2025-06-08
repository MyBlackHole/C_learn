/**
 * \brief backtrace测试程序
 *
 * 编译指令：gcc -g -rdynamic backtrace.c -o backtrace
 */

#include <execinfo.h> /* for backtrace() */
#include <signal.h> /* for signal */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 100

void dump(void)
{
	int index;
	int nptrs;
	void *buffer[100];
	char **strings;

	nptrs = backtrace(buffer, SIZE);
	printf("backtrace() returned %d addresses\n", nptrs);

	strings = backtrace_symbols(buffer, nptrs);
	if (strings == NULL) {
		perror("backtrace_symbols");
		exit(EXIT_FAILURE);
	}

	for (index = 0; index < nptrs; index++) {
		printf("  [%02d] %s\n", index, strings[index]);
	}

	free(strings);
}

void handler(int signo)
{
	printf("\n[catch signal %d (%s)]\n", signo, strsignal(signo));
	printf("Dump stack start...\n");
	dump();
	printf("Dump stack end...\n");

	/* 恢复并发送信号 */
	signal(signo, SIG_DFL);
	raise(signo);
}

void printSigno(int signo)
{
	static int i = 0;

	printf("\n[catch signal %d (%s) i=%d ]\n", signo, strsignal(signo),
	       i++);
	printf("Dump stack start...\n");
	dump();
	printf("Dump stack end...\n");
}

void myfunc3(void)
{
	/* 为SIGINT安装信号处理函数，通过Ctrl + C发出该信号 */
	signal(SIGINT, handler);
	signal(SIGSEGV, handler); /* 为安装SIGSEGV信号处理函数 */
	signal(SIGUSR1, printSigno);

	/* 打印当前函数调用栈 */
	printf("Current function calls list is: \n");
	printf("----------------------------------\n");
	dump();
	printf("----------------------------------\n\n");

	while (1) {
		; /* 在这里通过Ctrl + C发出一个SIGINT信号来结束程序的运行 */
	}
}

/**
 * \brief
 * 使用static修饰函数，表明不导出这个符号。
 * 即使用-rdynamic选项，看到的只能是个地址。
 */
static void myfunc2(void)
{
	myfunc3();
}

#define MAX_CALLS 100;

void myfunc(int ncalls)
{
	static int call_count = MAX_CALLS;
	if (call_count <= 0) {
		printf("Maximum number of calls reached.\n");
		exit(EXIT_FAILURE);
	}

	if (ncalls > 1) {
		/*myfunc(ncalls - 1);*/
	} else {
		myfunc2();
	}
	return;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "%s num-calls\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	myfunc(atoi(argv[1]));
	exit(EXIT_SUCCESS);
}

// ----------------------------------------------------------------------------
// End of backtrace.c
