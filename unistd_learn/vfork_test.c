#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int demo_vfork_main(void)
{
	int count = 1;
	int child;

	// 函数“vfork”不安全，因为它可能导致父进程中出现拒绝服务情况；
	// 应该使用 'posix_spawn' 代替
	child = vfork();

	if (child < 0) {
		perror("fork error : ");
	} else if (child == 0) {
		++count;
		printf("in child process, pid=%d, count=%d (%p)\n", getpid(),
		       count, &count);
		sleep(2);
		printf("pid=%d sleep 2 seconds, and now quit...\n", getpid());
		exit(0);
	} else {
		++count;
		printf("in parent process, pid=%d, count=%d (%p)\n", getpid(),
		       count, &count);
		printf("pid=%d quit now...\n", getpid());
		exit(0);
	}

	return EXIT_SUCCESS;
}
