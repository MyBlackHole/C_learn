#include "debug.h"

#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	uint64_t t;
	double t1;
	// 1647484871704308
	t = debug_time_usec();
	// 1647484871.704308
	t1 = debug_time_sec();
	printf("%ld\n", t);
	printf("%f\n", t1);
	return 0;
}
