#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int demo_SSH1_main(int argc, char **argv)
{
	int fd = 0;
	pid_t pid = 0;

	/*fd = open("SSH_stdout.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);*/
	fd = open("SSH_stdout.txt", O_WRONLY | O_CREAT | O_CLOEXEC | O_TRUNC, 0666);
	if (fd < 0) {
		perror("open error");
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == 0) {

		setsid();

		//子进程中，此描述符并不关闭，仍可使用
		write(fd, "child process\n", 15);

		//execl执行的程序里，此描述符被关闭，不能再使用它
		dup2(fd, STDOUT_FILENO);

		int flag;
		int ret = 0;
		flag = fcntl(STDIN_FILENO, F_GETFD);
		flag |= FD_CLOEXEC;
		ret = fcntl(STDIN_FILENO, F_SETFD, flag);
		if (ret < 0) {
			perror("fcntl STDIN_FILENO error");
			exit(EXIT_FAILURE);
		}

		flag = fcntl(STDOUT_FILENO, F_GETFD);
		flag |= FD_CLOEXEC;
		ret = fcntl(STDOUT_FILENO, F_SETFD, flag);
		if (ret < 0) {
			perror("fcntl STDOUT_FILENO error");
			exit(EXIT_FAILURE);
		}

		flag = fcntl(STDERR_FILENO, F_GETFD);
		flag |= FD_CLOEXEC;
		ret = fcntl(STDERR_FILENO, F_SETFD, flag);
		if (ret < 0) {
			perror("fcntl STDERR_FILENO error");
			exit(EXIT_FAILURE);
		}

		char *child_args[] = {"/usr/bin/sleep", "20",  NULL };
		execv("/usr/bin/sleep", child_args);
		perror("execv error");
		close(fd);
		exit(EXIT_FAILURE);
	}

	/*waitpid(pid, NULL, 0);*/
	write(fd, "parent process\n", 16);
	close(fd);
	exit(EXIT_SUCCESS);
}

// output: (O_CLOEXEC FD_CLOEXEC 设置前)
// ❯ ls -alh /proc/1706894/fd
// Permissions Size User  Date Modified Name
// lrwx------     - black 21 Sep 10:45   0 -> /dev/pts/9
// l-wx------     - black 21 Sep 10:45   1 -> /run/media/black/Data/Documents/c/build/linux/x86_64/debug/SSH_stdout.txt
// lrwx------     - black 21 Sep 10:45   2 -> /dev/pts/9
// lrwx------     - black 21 Sep 10:45   3 -> anon_inode:[eventpoll]
// lrwx------     - black 21 Sep 10:45   4 -> socket:[11157234]
// lrwx------     - black 21 Sep 10:45   5 -> socket:[11157235]
// l-wx------     - black 21 Sep 10:45   6 -> /run/media/black/Data/Documents/c/build/linux/x86_64/debug/SSH_stdout.txt
//
//
// output: (O_CLOEXEC FD_CLOEXEC 设置后), 0、1、2 都不存在
// ❯ ls -alh /proc/1673118/fd
// Permissions Size User  Date Modified Name
// lrwx------     - black 21 Sep 10:42   3 -> anon_inode:[eventpoll]
// lrwx------     - black 21 Sep 10:42   4 -> socket:[10935481]
// lrwx------     - black 21 Sep 10:42   5 -> socket:[10935482]
//
//
// // SSH test
// output: (setsid FD_CLOEXEC 设置, not waitpid), 立即退出, sleep 20 进程仍在运行
//
// ssh black@127.0.0.1 "/run/media/black/Data/Documents/c/build/linux/x86_64/debug/fcntl_learn SSH1"
//
// output: (setsid O_CLOEXEC FD_CLOEXEC 设置, not waitpid), 立即退出, sleep 20 进程仍在运行
