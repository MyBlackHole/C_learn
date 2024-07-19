#define _GNU_SOURCE
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <unistd.h>

// 该系统调用用于创建一个新的子进程，类似fork(2)。与fork(2)相比,
// 它可以更精确地控制调用进程和子进程之间的执行上下文细节。
// 例如，使用这些系统调用，调用者可以控制两个进程之间是否共享虚拟地址空间,
// 文件描述符表以及信号句柄表等。也可以通过这些系统调用将子进程放到不同的命名空间中。

#define STACK_SIZE (1024 * 1024)

static char child_stack[STACK_SIZE];

int child_main(void *args)
{
	printf("in child process, pid=%d\n", getpid());
	printf("quit child process...\n");
	return EXIT_SUCCESS;
}
int main()
{
	printf("start...\n");
	printf("in parent process, pid=%d\n", getpid());
	int child_pid =
		clone(child_main, child_stack + STACK_SIZE, SIGCHLD, NULL);
	waitpid(child_pid, NULL, 0);
	printf("quit...\n");
	return EXIT_SUCCESS;
}
