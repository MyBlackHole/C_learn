#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FNAME "/tmp/out"

int demo_dup2_main(int argc, char *argv[])
{
	int sfd = 0;
	int dfd = 0;
	int status = 0;
	(void)status;
	sfd = open(FNAME, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (sfd < 0) {
		perror("open()");
		exit(EXIT_FAILURE);
	}

	printf("%d\n", sfd);

	// 重定向 stdout 到文件
	// fd 肯能等于 1
	dfd = dup2(sfd, STDOUT_FILENO);
	close(sfd);
	if (dfd < 0) {
		perror("dup()");
		exit(EXIT_FAILURE);
	}
	puts("black");
	exit(EXIT_SUCCESS);
}
