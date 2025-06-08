/*
 * Copyright (c) 2014  Wu, Xingbo <wuxb45@gmail.com>
 *
 * All rights reserved. No warranty, explicit or implicit, provided.
 */

#define _GNU_SOURCE
#define _LARGEFILE64_SOURCE

#include <execinfo.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// 获取时间,单位微秒
uint64_t debug_time_usec(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000lu + tv.tv_usec;
}

// 获取时间, 单位秒
double debug_time_sec(void)
{
	const uint64_t usec = debug_time_usec();
	return ((double)usec) / 1000000.0;
}

// 获取时间差值,单位微秒
uint64_t debug_diff_usec(const uint64_t last)
{
	return debug_time_usec() - last;
}

// 获取时间差值,单位秒
double debug_diff_sec(const double last)
{
	return debug_time_sec() - last;
}

// 获取 timeval 的时间差值, 返回单位微秒
uint64_t debug_tv_diff(const struct timeval *const t0,
		       const struct timeval *const t1)
{
	return UINT64_C(1000000) * (t1->tv_sec - t0->tv_sec) +
	       (t1->tv_usec - t0->tv_usec);
}

void debug_print_tv_diff(char *tag, const struct timeval t0,
			 const struct timeval t1)
{
	printf("%s: %lu us\n", tag, debug_tv_diff(&t0, &t1));
}

// 打印函数调用堆栈信息
void debug_trace(void)
{
	void *array[100];
	char **strings;

	const int size = backtrace(array, 100);
	strings = backtrace_symbols(array, size);

	printf("Obtained %d stack frames.\n", size);

	int i;
	for (i = 0; i < size; i++) {
		printf("%d -> %s\n", i, strings[i]);
	}

	free(strings);
}
