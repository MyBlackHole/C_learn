#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUFFER_SIZE 65536 /* 64KB */
#define BUFFER_SIZE 4096 /* 4KB */
/*#define BUFFER_SIZE 1024*/

int demo_pipe2_main(int argc, char *argv[])
{
	int pipefd[2];
	pid_t cpid;
	char buf[MAX_BUFFER_SIZE];
	char buf_a[BUFFER_SIZE];
	int count;
	int read_size;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <count>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	memset(buf_a, 'a', BUFFER_SIZE);
	count = atoi(argv[1]);
	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	/*if (pipe2(pipefd, O_CLOEXEC | O_NONBLOCK) == -1) {*/
	/*	perror("pipe");*/
	/*	exit(EXIT_FAILURE);*/
	/*}*/
	fcntl(pipefd[0], F_SETPIPE_SZ, BUFFER_SIZE);
	fcntl(pipefd[1], F_SETPIPE_SZ, BUFFER_SIZE);
	cpid = fork();
	if (cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (cpid == 0) {
		/*printf("Child process started\n");*/
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) < 0) {
			perror("dup2");
			exit(EXIT_FAILURE);
		}

		while (count) {
			buf_a[0] = count + 48;
			printf("%s", buf_a);
			count--;
			/*sleep(1);*/
		}
		close(pipefd[1]);
		_exit(EXIT_SUCCESS);
	} else {
		/*printf("Parent process started\n");*/
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) < 0) {
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		while (count) {
			/*printf("Reading from pipe, count = %d\n", count);*/
			memset(buf, 0, MAX_BUFFER_SIZE);
			if ((read_size = read(STDIN_FILENO, &buf, MAX_BUFFER_SIZE)) < 0) {
				if (errno != EAGAIN) {
					perror("read");
					exit(EXIT_FAILURE);
				}
			} else if (read_size == 0) {
				printf("EOF reached\n");
				break;
			} else {
				count--;
			}
			printf("read_size = %d, [%s]\n", read_size, buf);
			read_size = 0;
			/*sleep(1);*/
		}
		close(pipefd[0]); /* Reader will see EOF */
		wait(NULL); /* Wait for child */
		exit(EXIT_SUCCESS);
	}
}
