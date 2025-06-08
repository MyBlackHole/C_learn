#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char *env = "USER_HOME";
	/* 设置环境变量 */
	putenv("USER_HOME=/user/root");

	/* 读取环境变量 */
	char *a = getenv(env);
	if (a != NULL) {
		printf("env :%s\n", a);
	}
	pause();
	return 0;
}
