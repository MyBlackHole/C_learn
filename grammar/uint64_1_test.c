#include <stdint.h>
#include <stdio.h>
#include <strings.h>

#define BASE 10
#define OFFSET 32
#define LSNNUM 18

int demo_uint64_1_main(int argc, char *argv[])
{
	// 18446744073709551615
	uint64_t timetemp = -1;
	printf("timetemp: %lu\n", timetemp);
	return 0;
}


// Output:
// ❯ xmake run grammar uint641
// timetemp: 18446744073709551615%
// In [2]: time.localtime(1844674407)
// Out[2]: time.struct_time(tm_year=2028, tm_mon=6, tm_mday=15, tm_hour=17, tm_min=33, tm_sec=27, tm_wday=3, tm_yday=167, tm_isdst=0)
