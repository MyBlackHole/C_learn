#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define NUM 60

enum {
	SECS_TO_SLEEP = 0,
	NSEC_TO_SLEEP = 10000000,
};

int demo_print_time_main(int argc, char *argv[])
{
	struct tm tm_tmp;
	time_t t_tmp;
	char data_time[NUM];
	int ret;
	struct timespec remaining;
	struct timespec request = { SECS_TO_SLEEP, NSEC_TO_SLEEP };

	while (1) {
		t_tmp = time(NULL);

		ret = nanosleep(&request, &remaining);
		// rv = nanosleep(&request, NULL);
		if (ret != 0) {
			printf("error: sleep: %s", strerror(errno));
			exit(EXIT_FAILURE);
		}

		strftime(data_time, sizeof(data_time), "%Y-%m-%d %H:%M:%S",
			 gmtime_r(&t_tmp, &tm_tmp));
		printf("******************************************************** ");
		printf("增加中文测试 %s\n", data_time);
		// // 刷新系统缓冲区
		// sync();
	}
	return EXIT_SUCCESS;
}
