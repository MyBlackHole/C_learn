#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* 定义一个给 clone 用的栈，栈大小1M */
#define STACK_SIZE (1024 * 1024)
static char container_stack[STACK_SIZE];

char *const container_args[] = { "/bin/bash", NULL };

int container_main(void *arg)
{
	printf("Container [%5d] - inside the container!\n", getpid());
	printf("Container - inside the container!\n");
	sethostname("container", 10); /* 设置hostname */
	execv(container_args[0], container_args);
	printf("Something's wrong!\n");
	return 1;
}

int main()
{
	printf("Parent - start a container!\n");
	/* 调用clone函数，其中传出一个函数，还有一个栈空间的（为什么传尾指针，因为栈是反着的）
     */
	int container_pid = clone(
		container_main, container_stack + STACK_SIZE,
		SIGCHLD | CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID, NULL);
	/* 等待子进程结束 */
	waitpid(container_pid, NULL, 0);
	printf("Parent - container stopped!\n");
	return 0;
}
