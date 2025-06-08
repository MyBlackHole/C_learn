#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/poll.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

/*#define BUFFER_SIZE 165536*/
#define BUFFER_SIZE 65536
/*#define BUFFER_SIZE 4096*/
/*#define BUFFER_SIZE 64*/

static pid_t *childpid = NULL;
/* ptr to array allocated at run-time */
static int maxfd; /* from our open_max(), {Prog openmax} */

#define SHELL "/bin/sh"

FILE *my_popen(const char *cmdstring, const char *type)
{
	int i, pfd[2];
	pid_t pid;
	FILE *fp;

	/* only allow "r" or "w" */
	if ((type[0] != 'r' && type[0] != 'w') || type[1] != 0) {
		errno = EINVAL; /* required by POSIX.2 */
		return (NULL);
	}

	if (childpid == NULL) { /* first time through */
		/* allocate zeroed out array for child pids */
		maxfd = 20;
		if ((childpid = calloc(maxfd, sizeof(pid_t))) == NULL)
			return (NULL);
	}

	if (pipe2(pfd, O_CLOEXEC | O_NONBLOCK) < 0)
		/*if (pipe(pfd) < 0)*/
		return (NULL); /* errno set by pipe() */

	if ((pid = fork()) < 0)
		return (NULL); /* errno set by fork() */
	else if (pid == 0) { /* child */
		if (*type == 'r') {
			close(pfd[0]);
			if (pfd[1] != STDOUT_FILENO) {
				dup2(pfd[1], STDOUT_FILENO);
				close(pfd[1]);
			}
		} else {
			close(pfd[1]);
			if (pfd[0] != STDIN_FILENO) {
				dup2(pfd[0], STDIN_FILENO);
				close(pfd[0]);
			}
		}
		/* close all descriptors in childpid[] */
		for (i = 0; i < maxfd; i++)
			if (childpid[i] > 0)
				close(i);

		execl(SHELL, "sh", "-c", cmdstring, (char *)0);
		_exit(127);
	}
	/* parent */
	if (*type == 'r') {
		close(pfd[1]);
		if ((fp = fdopen(pfd[0], type)) == NULL)
			return (NULL);
	} else {
		close(pfd[0]);
		if ((fp = fdopen(pfd[1], type)) == NULL)
			return (NULL);
	}
	childpid[fileno(fp)] = pid; /* remember child pid for this fd */
	return (fp);
}

int my_pclose(FILE *fp)
{
	int fd, stat;
	pid_t pid;

	if (childpid == NULL)
		return (-1); /* popen() has never been called */

	fd = fileno(fp);
	if ((pid = childpid[fd]) == 0)
		return (-1); /* fp wasn't opened by popen() */

	childpid[fd] = 0;
	if (fclose(fp) == EOF)
		return (-1);

	while (waitpid(pid, &stat, 0) < 0)
		if (errno != EINTR)
			return (-1); /* error other than EINTR from waitpid() */

	return (stat); /* return child's termination status */
}

inline static int read_is_ready2(int p_fd, const unsigned int time_ms)
{
	int ret = 0;
	struct pollfd fds;
	const int timeout = time_ms;
	memset(&fds, 0x00, sizeof(fds));
	fds.fd = p_fd;
	fds.events = POLLIN;
	if ((ret = poll(&fds, 1, timeout)) < 0) {
		printf("fd: %d, ret: %d, timeout: %d, %s(errno: %d)\n", p_fd,
		       ret, timeout, strerror(errno), errno);
	} else if (fds.revents & POLLIN) {
		return 1;
		/*} else if (fds.revents & (POLLHUP)) {*/
		/*	printf("fd: %d, ret: %d, revents: %d, %s(errno: %d)", p_fd, ret,*/
		/*	       fds.revents, strerror(errno), errno);*/
		/*	return 1;*/
	} else if (fds.revents & (POLLHUP | POLLERR)) {
		printf("fd: %d, ret: %d, revents: %d, %s(errno: %d)\n", p_fd,
		       ret, fds.revents, strerror(errno), errno);
		return -1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	FILE *p_fp;
	char buffer[BUFFER_SIZE];
	int64_t nbytes = 0;
	int ready = 0;

	if (argc != 3) {
		printf("Usage: %s test command\n", argv[0]);
		return EXIT_FAILURE;
	}
	p_fp = my_popen(argv[2], "r");
	/*p_fp = popen(argv[2], "r");*/
	/*p_fp = popen("cat /etc/passwd", "r");*/
	// 打印所有内容
	if (strcmp(argv[1], "fgets") == 0) {
		while (fgets(buffer, BUFFER_SIZE, p_fp) != NULL) {
			printf("%s", buffer);
		}
	} else {
		while (1) {
			ready = read_is_ready2(fileno(p_fp), 100);
			if (ready == 1) {
				/*nbytes = fread(buffer, 1, BUFFER_SIZE, p_fp);*/
				nbytes =
					read(fileno(p_fp), buffer, BUFFER_SIZE);
				if (nbytes == 0) {
					break;
				}
				buffer[nbytes] = 0x00;
				printf("%s", buffer);
			} else if (ready == 0) {
			} else {
				printf("pipe close");
				break;
			}
		}
	}

	my_pclose(p_fp);
	/*pclose(p_fp);*/
	return EXIT_SUCCESS;
}
