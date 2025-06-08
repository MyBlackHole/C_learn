#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum { SECS_TO_SLEEP = 3, NSEC_TO_SLEEP = 125 };

int demo_nanosleep_main(int argc, char *argv[])
{
	struct timespec remaining, request = { SECS_TO_SLEEP, NSEC_TO_SLEEP };
	int rv;
	struct tm t;
	char data_time[64];

	printf("time test\n");

	for (int i = 0; i < 10; ++i) {
		// 休眠
		rv = nanosleep(&request, &remaining);
		// rv = nanosleep(&request, NULL);
		if (rv != 0) {
			printf("error: sleep: %s", strerror(errno));
		}
		strftime(data_time, sizeof(data_time), "%Y-%m-%d %H:%M:%S",
			 localtime_r(&request.tv_sec, &t));
		printf("data_time=%s, tv_nsec=%ld\n", data_time,
		       request.tv_nsec);
	}

	exit(EXIT_SUCCESS);
}
