#define _GNU_SOURCE
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <sys/capability.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <unistd.h>

#define STACK_SIZE (1024 * 1024)

static char child_stack[STACK_SIZE];
char *const child_args[] = { "/bin/bash", NULL };

void set_uid_map(pid_t pid, int inside_id, int outside_id, int length)
{
	char path[256];
	sprintf(path, "/proc/%d/uid_map", pid);
	FILE *uid_map = fopen(path, "w");
	fprintf(uid_map, "%d %d %d", inside_id, outside_id, length);
	fclose(uid_map);
}

void set_gid_map(pid_t pid, int inside_id, int outside_id, int length)
{
	char path[256];
	sprintf(path, "/proc/%d/gid_map", pid);
	FILE *gid_map = fopen(path, "w");
	fprintf(gid_map, "%d %d %d", inside_id, outside_id, length);
	fclose(gid_map);
}

int child_main(void *args)
{
	printf("in child process\n");
	cap_t caps;
	set_uid_map(getpid(), 0, 1000, 1);
	set_gid_map(getpid(), 0, 1000, 1);
	printf("eUID = %ld; eGID = %ld; ", (long)geteuid(), (long)getegid());
	caps = cap_get_proc();
	printf("capabilities: %s\n", cap_to_text(caps, NULL));
	execv(child_args[0], child_args);
	printf("quit child process…\n");
	return 1;
}

// CLONE_NEWUSER
// 此标志最先在Linux 2.6.23中的clone()中启用，当前的clone()语义已在Linux 3.5中合入，而完整可用的用户空间功能在Linux
// 3.8中合入。 如果设置了CLONE_NEWUSER ，则会在新的用户命
// 空间中创建进程。如果没有设置该标志，则新创建的进程与调用进程的用户命名空间相同。
// 在Linux 3.8之前，使用CLONE_NEWUSER 要求具有3个capability：CAP_SYS_ADMIN,
// CAP_SETUID 和CAP_SETGID。 Linux 3.8开始，创建用户命名空间不需要特权。
// 该标志不能与CLONE_THREAD 或CLONE_PARENT配合使用。出于安全因素，CLONE_NEWUSER
// 不能与CLONE_FS配合使用(不同的文件具有不同的用户标志，Linux
//

int main()
{
	printf("start parent ...\n");
	int child_pid = clone(child_main, child_stack + STACK_SIZE,
			      CLONE_NEWUSER | SIGCHLD, NULL);
	waitpid(child_pid, NULL, 0);
	printf("quit parent ...\n");
	return 0;
}
