#define _GNU_SOURCE
#include <fcntl.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define STACK_SIZE (1024 * 1024)

int idle(void *args)
{
	printf("I'm child process, and my pid is: %d\n", getpid());
	for (;;) {
		sleep(1);
	}

	return 0;
}

pid_t clone_wrapper(int (*func)(void *), int flag, void *args)
{
	char *stack, *stack_top;

	stack = (char *)malloc(STACK_SIZE);
	if (stack == NULL) {
		printf("alloc stack for child failed!\n");
		return -1;
	}
	// 栈是倒过来的
	stack_top = stack + STACK_SIZE; /* Assume stack grows downward */

	return clone(func, stack_top, flag, args);
}

// 获取指定 pid 的 pid 命名空间 路径
char *get_pid_ns(int pid)
{
	char bytes[32];

	sprintf(bytes, "/proc/%d/ns/pid", pid);
	return strdup(bytes);
}

// sudo ./out/obj/sched_learn/setns_test
int main(void)
{
	pid_t childs[2];
	char *ns_file;
	int fd;

	printf("I'm parent, and my pid is: %d\n", getpid());

	childs[0] = clone_wrapper(idle, CLONE_NEWPID, NULL);
	if (childs[0] == -1) {
		printf("error: create child thread failed!\n");
		return EXIT_FAILURE;
	}
	printf("first child's pid is: %d\n", childs[0]);

	ns_file = get_pid_ns(childs[0]);
	if (!ns_file) {
		printf("get child pid ns failed!\n");
		return -1;
	}

	fd = open(ns_file, O_RDONLY);
	if (fd == -1) {
		printf("open child pid ns failed!\n");
		return -1;
	}

	// 修改命名空间

	// // 不验证 命名空间, 直接设置
	// if (setns(fd, 0) == -1)
	if (setns(fd, CLONE_NEWPID) == -1) {
		printf("set ns failed!\n");
		return -1;
	}

	printf("I'm parent, and my pid is: %d\n", getpid());

	// 继承命名空间
	childs[1] = clone_wrapper(idle, 0, NULL);
	if (childs[1] == -1) {
		printf("error: create child thread failed!\n");
		return -1;
	}
	printf("second child's pid is: %d\n", childs[1]);

	sleep(3);

	kill(childs[0], SIGTERM);
	kill(childs[1], SIGTERM);

	waitpid(childs[0], NULL, 0);
	waitpid(childs[1], NULL, 0);

	return EXIT_SUCCESS;
}
