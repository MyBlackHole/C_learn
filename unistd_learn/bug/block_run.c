#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUF_NUM 50
#define SECONDS 1000

// ./out/obj/unistd_learn/bug/block_run
// /media/black/Data/Documents/C/out/obj/unistd_learn/bug/setsid_test
int main(int argc, char *argv[])
{
	char buf[BUF_NUM] = {};
	pid_t pid;
	int pin[2];
	int pout[2];
	int perr[2];
	int ret;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (pipe(pin) == -1) {
		fprintf(stderr, "pipe in: %.100s", strerror(errno));
		return EXIT_FAILURE;
	}
	if (pipe(pout) == -1) {
		fprintf(stderr, "pipe out: %.100s", strerror(errno));
		close(pin[0]);
		close(pin[1]);
		return EXIT_FAILURE;
	}
	if (pipe(perr) == -1) {
		fprintf(stderr, "pipe err: %.100s", strerror(errno));
		close(pin[0]);
		close(pin[1]);
		close(pout[0]);
		close(pout[1]);
		return EXIT_FAILURE;
	}

	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) {
		// 处理基本的三个流 fd
		close(pin[1]);
		if (dup2(pin[0], STDIN_FILENO) == -1) {
			perror("dup2 stdin");
		}
		close(pin[0]);

		close(pout[0]);
		if (dup2(pout[1], STDOUT_FILENO) == -1) {
			perror("dup2 stdout");
		}
		close(pout[1]);

		close(perr[0]);
		if (dup2(perr[1], STDERR_FILENO) == -1) {
			perror("dup2 stderr");
		}
		close(perr[1]);

		char *property[] = { NULL };
		// char *envp[] = {"PATH=/bin", NULL};

		ret = execve(argv[1], property, NULL);
		if (ret == -1) {
			fprintf(stderr, "execve start err %.100s",
				strerror(errno));
			exit(EXIT_FAILURE);
		} else {
			// 无法到达这里
			_exit(EXIT_SUCCESS);
		}
	} else {
		close(pin[0]);
		close(pout[1]);
		close(perr[1]);

		fprintf(stdout, "block_run pid:%d\n", getpid());
		while (true) {
			printf("模仿读取\n");
			// 模仿读取
			read(pout[0], buf, BUF_NUM);
			printf("pout %s\n", buf);
			memset(buf, 0, BUF_NUM);
			// read(perr[0], buf, BUF_NUM);
			// printf("perr %s\n", buf);
			// memset(buf, 0, BUF_NUM);
			sleep(1);
		}
		sleep(SECONDS);

		// 等待儿子退出
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
}
