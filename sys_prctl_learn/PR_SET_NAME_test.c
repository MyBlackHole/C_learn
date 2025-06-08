/*
gcc changetitle.c -o changetitle
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <unistd.h>

int demo_PR_SET_NAME_main(int argc, char *argv[], char *envp[])
{
	int ret;
	char *old_name = malloc(255);
	char *new_name = "littlehann-program";

	if (old_name == NULL) {
		exit(EXIT_FAILURE);
	}
	ret = prctl(PR_GET_NAME, old_name);
	if (ret < 0) {
		printf("PR_GET_NAME error");
		exit(EXIT_FAILURE);
	}
	printf("old: %s\n", old_name);

	prctl(PR_SET_NAME, new_name);
	if (ret < 0) {
		printf("PR_SET_NAME error");
		exit(EXIT_FAILURE);
	}

	ret = prctl(PR_GET_NAME, old_name);
	if (ret < 0) {
		printf("PR_GET_NAME error");
		exit(EXIT_FAILURE);
	}
	printf("new: %s - %d\n", old_name, getpid());

	sleep(1000);

	free(old_name);
	return EXIT_SUCCESS;
}
