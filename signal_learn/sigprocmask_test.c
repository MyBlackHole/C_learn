#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * sigprocmask: 设置或者查询信号启用状态
 */

int demo_sigprocmask_main()
{
	sigset_t set;
	sigprocmask(0, NULL, &set);
	for (int i = 0; i < _SIGSET_NWORDS; i++) {
		printf("__val[%d] - %ld\n", i, set.__val[i]);
	}
	exit(0);
}
