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
	printf("quit child process��\n");
	return 1;
}

// CLONE_NEWPID (since Linux 2.6.24)
// ���������CLONE_NEWPID ��������µ�PID
// ���ռ��д������̡����û�����øñ�־�����´����Ľ�������ý��̵�PID�����ռ���ͬ��
// ֻ����Ȩ����(CAP_SYS_ADMIN)�ſ�������CLONE_NEWPID��������һ��clone������ͬʱָ��CLONE_NEWPID
// ��CLONE_THREAD /CLONE_PARENT(CLONE_THREAD����CLONE
// PARENT���޸Ľ�����������໥ì�ܵ�
// ����ʹ��nsenter -t <PID> -p����PID�����ռ䣬ʹ��ps����鿴������Ϣ��

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
