#define _GNU_SOURCE
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <unistd.h>

#define STACK_SIZE (1024 * 1024)

static char child_stack[STACK_SIZE];
char *const child_args[] = { "/bin/bash", NULL };

int child_main(void *args)
{
	printf("in child process\n");
	sethostname("NewHostName", 12);
	execv(child_args[0], child_args);
	printf("quit child process…\n");
	return 1;
}

// CLONE_NEWPID (since Linux 2.6.24)
// 如果设置了CLONE_NEWPID ，则会在新的PID
// 名空间中创建进程。如果没有设置该标志，则新创建的进程与调用进程的PID命名空间相同。
// 只有特权进程(CAP_SYS_ADMIN)才可以设置CLONE_NEWPID。不能在一个clone调用中同时指定CLONE_NEWPID
// 和CLONE_THREAD /CLONE_PARENT(CLONE_THREAD和这CLONE
// PARENT会修改进程树，因此相互矛盾的
// 可以使用nsenter -t <PID> -p进入PID命名空间，使用ps命令查看进程信息。

int main()
{
	printf("start parent process...\n");
	int child_pid = clone(
		child_main, child_stack + STACK_SIZE,
		CLONE_NEWPID | CLONE_NEWIPC | CLONE_NEWUTS | SIGCHLD, NULL);
	waitpid(child_pid, NULL, 0);
	printf("quit parent process...\n");
	return 0;
}
