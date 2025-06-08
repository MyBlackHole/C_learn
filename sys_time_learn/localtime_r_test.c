#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

int get_tm(struct tm *p_tm)
{
	int ret = 0;
	time_t time_real;
	time_real = time(NULL);
	if (time_real == (time_t)-1) {
		ret = -errno;
		goto out;
	}
	if (!localtime_r(&time_real, p_tm)) {
		ret = -errno;
		goto out;
	}
out:
	return ret;
}

static void *func()
{
	int ret = 0;
	struct tm tm;
	ret = get_tm(&tm);
	if (ret) {
		fprintf(stderr, "get_tm() failed: %d\n", ret);
	}
	printf("Year: %d\n", tm.tm_year + 1900);
	printf("Month: %d\n", tm.tm_mon + 1);
	printf("Day: %d\n", tm.tm_mday);
	printf("Hour: %d\n", tm.tm_hour);
	printf("Minute: %d\n", tm.tm_min);
	printf("Second: %d\n", tm.tm_sec);
	return 0;
}

int demo_localtime_r_main(void)
{
	pthread_t tid1;
	pthread_t tid2;
	pthread_t tid3;

	pthread_create(&tid1, NULL, func, NULL);
	pthread_create(&tid2, NULL, func, NULL);
	pthread_create(&tid3, NULL, func, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	return 0;
}
