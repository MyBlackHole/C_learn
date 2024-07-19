#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
	char foo[] = "Hello proc-1 world";
	// 修改前的 foo
	printf("foo before modify: %s\n", foo);
	printf("./change  %d  %p  %ld\n", getpid(), foo, strlen(foo) + 1);
	// 中断，保证进程不会退出
	printf("Press any key\n");
	getchar();
	// 修改后的 foo 字符串
	printf("foo after modify: %s\n", foo);
	return 0;
}
