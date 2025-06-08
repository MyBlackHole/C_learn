#include <linux/prctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/prctl.h>
#include <unistd.h>

#define NUM 100
#define SECONDS 10

int main(int argc, char **argv)
{
	fprintf(stdout, "parent pid:%d\n", getpid());
	// 必须 fflush, 或者用直接 io 操作
	fflush(stdout);
	if (fork() > 0) {
		fprintf(stdout, "parent pid:%d\n", getpid());
		fflush(stdout);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		// printf("parent begin\n");

		// printf("parent exit\n");
		sleep(SECONDS);
		exit(EXIT_SUCCESS);
	}

	fprintf(stdout, "child pid:%d\n", getpid());
	fflush(stdout);
	/* 脱离父进程组 */
	setsid();
	prctl(PR_SET_NAME, "setsid child");

	// printf("child begin\n");

	for (size_t i = 0; i < NUM; i++) {
		fprintf(stdout, "child count:%ld pid:%d\n", i, getpid());
		fflush(stdout);
		sleep(SECONDS);
	}

	// printf("child exit\n");
	return EXIT_SUCCESS;
}
