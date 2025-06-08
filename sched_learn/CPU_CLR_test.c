#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(0, &set);
	// 从集合删除一个元素
	CPU_CLR(1, &set);
	CPU_CLR(2, &set);
	CPU_CLR(3, &set);

	// 如果pid的值为0,则表示指定的是当前进程,使当前进程运行在 set
	// 所设定的那些CPU上.
	int ret = sched_setaffinity(0, sizeof(cpu_set_t), &set);
	if (ret == -1) {
		perror("sched_getaffinity");
		exit(1);
	}

	for (int i = 0; i < CPU_SETSIZE; i++) {
		int cpu = CPU_ISSET(i, &set);
		printf("cpu=%i is %s\n", i, cpu ? "set" : "unset");
	}

	return 0;
}
