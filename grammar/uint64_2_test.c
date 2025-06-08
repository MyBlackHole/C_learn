#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

int demo_uint64_2_main(int argc, char *argv[])
{
	uint64_t x = 10000000000;
	uint64_t y = 1;
	uint64_t download_average_bandwidth = x / y;

	printf("x / y: %lu\n", download_average_bandwidth);
	return EXIT_SUCCESS;
}

// Output:
// ❯ xmake run grammar uint641
// timetemp: 18446744073709551615%
// In [2]: time.localtime(1844674407)
// Out[2]: time.struct_time(tm_year=2028, tm_mon=6, tm_mday=15, tm_hour=17, tm_min=33, tm_sec=27, tm_wday=3, tm_yday=167, tm_isdst=0)
