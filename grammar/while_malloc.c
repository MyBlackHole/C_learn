#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define MB (1024 * 1024)

#define GB (1024 * 1024 * 1024)

/*
 * 此案例用来测试 cgroup v2 cpu、memory 限制功能
 */
int demo_while_malloc_main()
{
	char *p;
	int i = 0;
	pid_t pid;
	pid = getpid();
	printf("Process ID: %d\n", pid);
	while (true) {
		if (i * MB < GB) {
			p = (char *)malloc(MB);
			memset(p, 0, MB);
			printf("%dM memory allocated\n", ++i);
		}
		sleep(1);
	}

	return EXIT_SUCCESS;
}
