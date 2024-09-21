#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int demo_FD_CLOEXEC_main(int argc, char **argv)
{
	int ret = 0;
	int fd = 0;
	pid_t pid = 0;
	int flag;

	fd = open("FD_CLOEXEC_stdout.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0) {
		perror("open error");
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == 0) {
		//子进程中，此描述符并不关闭，仍可使用
		write(fd, "child process\n", 15);

		//execl执行的程序里，此描述符被关闭，不能再使用它
		dup2(fd, STDOUT_FILENO);

		flag = fcntl(STDOUT_FILENO, F_GETFD);
		flag |= FD_CLOEXEC;
		ret = fcntl(STDOUT_FILENO, F_SETFD, flag);
		if (ret < 0) {
			perror("fcntl error");
			exit(EXIT_FAILURE);
		}

		char *child_args[] = { NULL };
		execv("/usr/bin/eza", child_args);
		perror("execv error");
		close(fd);
		exit(EXIT_FAILURE);
	}

	waitpid(pid, NULL, 0);
	write(fd, "parent process\n", 16);
	close(fd);
	exit(EXIT_SUCCESS);
}
