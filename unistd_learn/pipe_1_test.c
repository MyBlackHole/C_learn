#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int demo_pipe_1_main(int argc, char *argv[])
{
	int pipefd[2];
	pid_t cpid;
	int status;
	char read_buf = 'a';

	if (pipe(pipefd) < 0) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid = fork();
	if (cpid < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0) {
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(STDOUT_FILENO);
		close(pipefd[1]);
		sleep(10);

		exit(EXIT_SUCCESS);
	} else {
		close(pipefd[1]);
		read(pipefd[0], &read_buf, 1);
		printf("read data :%c\n", read_buf);
		wait(&status);
		printf("child exit status :%d\n", status);
		exit(EXIT_SUCCESS);
	}
}

// Output: (close(STDOUT_FILENO)), 堵塞10秒后，打印数据 a 和 0
// ❯ xmake run unistd_learn pipe_1
// read data :a
// child exit status :0
//
// Output: (close(pipefd[0]), close(STDOUT_FILENO)), 打印数据 a 后堵塞10秒，打印数据 0
// ❯ xmake run unistd_learn pipe_1
// read data :a
// child exit status :0
