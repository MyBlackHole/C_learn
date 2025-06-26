#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <errno.h>
#include <stdlib.h>

void os_setup_limits(bool max)
{
	struct rlimit nofile;

	if (getrlimit(RLIMIT_NOFILE, &nofile) < 0) {
		fprintf(stderr, "unable to query NOFILE limit: %s",
			strerror(errno));
		return;
	}

	if (!max && nofile.rlim_cur == nofile.rlim_max) {
		printf("NOFILE limit is already set to %lu\n", nofile.rlim_cur);
		return;
	}

#ifdef CONFIG_DARWIN
	nofile.rlim_cur = OPEN_MAX < nofile.rlim_max ? OPEN_MAX :
						       nofile.rlim_max;
#else
	nofile.rlim_cur = nofile.rlim_max;
	// // 不可靠
	// nofile.rlim_cur = RLIM_SAVED_CUR;
	// nofile.rlim_max = RLIM_SAVED_MAX;

	printf("Current NOFILE limit is %lu, setting to %lu\n", nofile.rlim_cur,
	       nofile.rlim_max);
#endif

	if (setrlimit(RLIMIT_NOFILE, &nofile) < 0) {
		fprintf(stderr, "unable to set NOFILE limit: %s\n",
			strerror(errno));
		return;
	}
}

int demo_setrlimit_1_main(int argc, char *argv[])
{
	char c;
	bool max = false;
	while ((c = getopt(argc, argv, "m")) != -1) {
		switch (c) {
		case 'm':
			max = true;
			break;
		default:
			fprintf(stderr, "Usage: %s [-m]\n", argv[0]);
			return EXIT_FAILURE;
		}
	}
	printf("Setting NOFILE limit\n");
	os_setup_limits(max);
	return EXIT_SUCCESS;
}
