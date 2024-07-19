#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int mysystem(const char *cmdstring)
{
	pid_t pid;
	int status;
	pid = fork();
	if (pid < 0) {
		status = -1;
	} else if (pid == 0) {
		execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
		_exit(EXIT_FAILURE);
	} else {
		while (waitpid(pid, &status, 0) < 0) {
			status = -1;
			break;
		}
	}
	return (status);
}

int demo_execl_main()
{
	char s[100];
	char *sp;
	while ((sp = fgets(s, 100, stdin)) != NULL) {
		mysystem(s);
	}
	return EXIT_SUCCESS;
}
