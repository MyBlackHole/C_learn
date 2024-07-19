#define _GNU_SOURCE
#include <errno.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
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

// CLONE_NEWIPC (since Linux 2.6.19)
// 如果设置了CLONE_NEWIPC ，则会在新的IPC
// 名空间中创建进程。如果没有设置该标志，则新创建的进程与调用进程的IPC命名空间相同。
// 只有特权进程(CAP_SYS_ADMIN)才可以设置CLONE_NEWIPC
// ，不能与CLONE_SYSVSEM共用(互 矛盾)。
int main()
{
	printf("start parent process...\n");
	int child_pid = clone(child_main, child_stack + STACK_SIZE,
			      CLONE_NEWIPC | CLONE_NEWUTS | SIGCHLD, NULL);
	if (child_pid < 0) {
		printf("child_pid: %d\n", child_pid);
		perror(strerror(errno));
	}
	waitpid(child_pid, NULL, 0);
	printf("quit parent process...\n");
	return 0;
}
