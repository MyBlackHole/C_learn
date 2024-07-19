#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define PSCMD "ps -o pid,ppid,state,tty,command"

int main(void)
{
	setbuf(stdout, NULL);

	pid_t pid;
	if ((pid = fork()) < 0) {
		perror("fork error");
		exit(1);
	} else if (pid == 0) {
		exit(0);
	}
	// 父进程
	sleep(4);
	system(PSCMD);
	printf("ok");
	exit(0);
}
