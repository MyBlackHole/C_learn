#include <stdio.h>
#include <endian.h>

int demo_BYTE_ORDER_main(int argc, const char *argv[])
{
	if (__BYTE_ORDER == __LITTLE_ENDIAN) {
		printf("LITTLE\n");
	} else if (__BYTE_ORDER == __BIG_ENDIAN) {
		printf("BIG\n");
	} else {
		printf("UNKNOW\n");
	}

	return 0;
}
