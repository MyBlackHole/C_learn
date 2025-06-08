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
	printf("quit child process��\n");
	return 1;
}

// CLONE_NEWUSER
// �˱�־������Linux 2.6.23�е�clone()�����ã���ǰ��clone()��������Linux 3.5�к��룬���������õ��û��ռ书����Linux
// 3.8�к��롣 ���������CLONE_NEWUSER ��������µ��û���
// �ռ��д������̡����û�����øñ�־�����´����Ľ�������ý��̵��û������ռ���ͬ��
// ��Linux 3.8֮ǰ��ʹ��CLONE_NEWUSER Ҫ�����3��capability��CAP_SYS_ADMIN,
// CAP_SETUID ��CAP_SETGID�� Linux 3.8��ʼ�������û������ռ䲻��Ҫ��Ȩ��
// �ñ�־������CLONE_THREAD ��CLONE_PARENT���ʹ�á����ڰ�ȫ���أ�CLONE_NEWUSER
// ������CLONE_FS���ʹ��(��ͬ���ļ����в�ͬ���û���־��Linux
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
