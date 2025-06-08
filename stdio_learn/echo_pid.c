#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int demo_echo_pid_main(int argc, char *argv[])
{
	int ret = 0;
	int pid_fd = 0;
	char *pid_file = NULL;
	int pid = 0;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s <pid_file> <pid>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	pid_file = argv[1];
	pid = atoi(argv[2]);

	pid_fd = open(pid_file, O_RDWR | O_CREAT, 0666);
	if (pid_fd <= 0) {
		return EXIT_FAILURE;
	}

	ret = pwrite(pid_fd, &pid, sizeof(pid), 0);
	if (ret <= 0) {
		fprintf(stderr, "can't write %s(%s)\n", pid_file,
			strerror(errno));
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
