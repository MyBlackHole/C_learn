#include <stdio.h>
#include <time.h>
#include <unistd.h>

static void clock_gettime_test()
{
	struct timespec ts;

	clock_gettime(CLOCK_REALTIME, &ts);
	printf("CLOCK_REALTIME(1) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);
	usleep(1000 * 1000);
	clock_gettime(CLOCK_REALTIME, &ts);
	printf("CLOCK_REALTIME(2) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);

	clock_gettime(CLOCK_MONOTONIC, &ts);
	printf("CLOCK_MONOTONIC(1) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);
	usleep(1000 * 1000);
	clock_gettime(CLOCK_MONOTONIC, &ts);
	printf("CLOCK_MONOTONIC(2) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
	printf("CLOCK_PROCESS_CPUTIME_ID(1) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);
	usleep(1000 * 1000);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
	printf("CLOCK_PROCESS_CPUTIME_ID(2) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);

	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
	printf("CLOCK_THREAD_CPUTIME_ID(1) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);
	usleep(1000 * 1000);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
	printf("CLOCK_THREAD_CPUTIME_ID(2) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);

	clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
	printf("CLOCK_MONOTONIC_RAW(1) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);
	usleep(1000 * 1000);
	clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
	printf("CLOCK_MONOTONIC_RAW(2) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);

	clock_gettime(CLOCK_REALTIME_COARSE, &ts);
	printf("CLOCK_REALTIME_COARSE(1) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);
	usleep(1000 * 1000);
	clock_gettime(CLOCK_REALTIME_COARSE, &ts);
	printf("CLOCK_REALTIME_COARSE(2) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);

	clock_gettime(CLOCK_MONOTONIC_COARSE, &ts);
	printf("CLOCK_MONOTONIC_COARSE(1) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);
	usleep(1000 * 1000);
	clock_gettime(CLOCK_MONOTONIC_COARSE, &ts);
	printf("CLOCK_MONOTONIC_COARSE(2) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);

	clock_gettime(CLOCK_BOOTTIME, &ts);
	printf("CLOCK_BOOTTIME(1) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);
	usleep(1000 * 1000);
	clock_gettime(CLOCK_BOOTTIME, &ts);
	printf("CLOCK_BOOTTIME(2) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);

	clock_gettime(CLOCK_REALTIME_ALARM, &ts);
	printf("CLOCK_REALTIME_ALARM(1) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);
	usleep(1000 * 1000);
	clock_gettime(CLOCK_REALTIME_ALARM, &ts);
	printf("CLOCK_REALTIME_ALARM(2) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);

	clock_gettime(CLOCK_BOOTTIME_ALARM, &ts);
	printf("CLOCK_BOOTTIME_ALARM(1) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);
	usleep(1000 * 1000);
	clock_gettime(CLOCK_BOOTTIME_ALARM, &ts);
	printf("CLOCK_BOOTTIME_ALARM(2) sec = %lu, nsec = %ld\n", ts.tv_sec,
	       ts.tv_nsec);

	clock_gettime(CLOCK_TAI, &ts);
	printf("CLOCK_TAI(1) sec = %lu, nsec = %ld\n", ts.tv_sec, ts.tv_nsec);
	usleep(1000 * 1000);
	clock_gettime(CLOCK_TAI, &ts);
	printf("CLOCK_TAI(2) sec = %lu, nsec = %ld\n", ts.tv_sec, ts.tv_nsec);
}

int demo_clock_gettime_main()
{
	clock_gettime_test();

	return 0;
}
