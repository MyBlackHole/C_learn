#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int demo_pipe_2_main(int argc, char *argv[])
{
	int pipefd[2];
	pid_t cpid;
	int status;
	char write_buf = '1';
	// char read_buf;

	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid = fork();
	if (cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0) {
		close(pipefd[0]);
		// 64 * 1024
		for (int i = 0; i < 64 * 1024; i++) {
			write(pipefd[1], &write_buf, 1);
		}

		// // 多写一个字节， 使其超过 64 * 1024 堵塞
		// write(pipefd[1], &write_buf, 1);

		// sleep(10);

		_exit(EXIT_SUCCESS);
	} else {
		close(pipefd[1]);
		// printf("start read\n");
		// read(pipefd[0], &read_buf, 1);
		// printf("read_buf :%c\n", read_buf);
		// close(pipefd[1]);
		wait(&status);
		printf("child exit status :%d\n", status);
		exit(EXIT_SUCCESS);
	}
}
