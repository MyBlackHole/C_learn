#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAXLINE 4048

static void sig_int(int signo);
int demo_signal_main(int argc, char **argv)
{
	char buf[MAXLINE]; // from apue.h referrnce
	pid_t pid;
	int status;
	if (signal(SIGINT, sig_int) == SIG_ERR) {
		perror("singal error");
		exit(1);
	}
	printf("%%");
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if ((buf[strlen(buf) - 1]) == '\n') {
			buf[strlen(buf) - 1] = 0; // relplace newline with null;
		}
		if ((pid = fork()) < 0) {
			perror("fork error");
			exit(1);
		} else if (pid == 0) {
			execlp(buf, buf, (char *)0);
			fprintf(stderr, "couldn't execute :%s ", buf);
			exit(127);
		}

		if ((pid = waitpid(pid, &status, 0)) < 0) {
			perror("waitpaid error");
			exit(1);
		}
		printf("%%");
	}
	exit(0);
}

void sig_int(int signo)
{
	printf("interrupt\n%%");
}
