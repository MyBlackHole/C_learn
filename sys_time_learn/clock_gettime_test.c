#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

int demo_clock_gettime_main(int argc, char **argv)
{
	struct timespec time_1 = { 0, 0 };
	struct timespec time_2 = { 0, 0 };

	int ret;
	float temp;

	/* 获取时间 */
	ret = clock_gettime(CLOCK_REALTIME, &time_1);
	if (ret < 0) {
		return EXIT_FAILURE;
	}
	/* 挂起程序 */
	sleep(1);
	ret = clock_gettime(CLOCK_REALTIME, &time_2);
	if (ret < 0) {
		return EXIT_FAILURE;
	}
	temp = (time_2.tv_nsec - time_1.tv_nsec) / 1000000;
	printf("time = %f ms\n", temp);
	printf("time = %ld ms\n", time_1.tv_sec);
	printf("time = %ld ms\n", time_2.tv_sec);
	return 0;
}
