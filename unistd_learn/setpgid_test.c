#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define SECONDS 5

int demo_setpgid_main()
{
	pid_t pid;
	pid_t old_pgid;
	pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(1);
	} else if (pid == 0) {
		old_pgid = getpgrp();
		printf("child process PID is: %d\n", getpid());
		printf("child process PGID is: %d\n", getpgrp());
		printf("child process PGID is: %d\n", old_pgid);

		sleep(SECONDS);

		// 改变子进程的组ID
		// setpgid(pid, pid);
		setpgid(pid, 0);

		printf("child old PGID %d changed to: %d\n", old_pgid,
		       getpgrp());

		exit(0);
	}
	old_pgid = getpgrp();
	printf("parent process PID is:  %d\n", getpid());
	printf("parent process PPID is: %d\n", getppid());
	printf("parent process PGID is: %d\n", old_pgid);

	// 改变父进程的组ID为父进程的父进程
	// setpgid(getpid(), getppid());
	setpgid(getpid(), 0);
	sleep(SECONDS);
	printf("parent old PGID %d changed to: %d\n", old_pgid, getpgrp());

	// 等待子进程结束
	if (waitpid(pid, NULL, 0) != pid) {
		perror("waitpid error");
	}
	return 0;
}
