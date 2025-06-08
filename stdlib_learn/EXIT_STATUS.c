#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int demo_exit_main(int argc, char *argv[])
{
	int ret;
	if (argc < 2) {
		printf("Usage: %s <exit status>\n", argv[0]);
		return EXIT_FAILURE;
	}
	sleep(10);
	ret = atoi(argv[1]);
	return ret;
}
