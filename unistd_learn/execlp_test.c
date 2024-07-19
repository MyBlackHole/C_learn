#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXLINE 4048

int demo_execlp_main(int argc, char **argv)
{
	char buf[MAXLINE]; // from apue.h referrnce
	pid_t pid;
	int status;
	printf("%%");
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if ((buf[strlen(buf) - 1]) == '\n') {
			buf[strlen(buf) - 1] = 0; // relplace newline with null;
		}
		pid = fork();
		if (pid < 0) {
			perror("fork error");
			exit(EXIT_FAILURE);
		} else if (pid == 0) {
			execlp(buf, buf, (char *)0);
			fprintf(stderr, "couldn't execute :%s ", buf);
			exit(EXIT_FAILURE);
		}
		pid = waitpid(pid, &status, 0);
		if (pid < 0) {
			perror("waitpaid error");
			exit(EXIT_FAILURE);
		}
		printf("%%");
	}
	exit(EXIT_SUCCESS);
}
