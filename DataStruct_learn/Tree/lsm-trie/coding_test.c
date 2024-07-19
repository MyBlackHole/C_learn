#include "coding.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
	uint8_t buf[20];
	const uint8_t *p = encode_uint64(buf, 4000);

	printf("[%d:%x]", 0, buf[0]);
	for (int i = 1; i < 20; i++) {
		printf("[%d:%x]", i, buf[i]);
	}
	printf("\n");
	fflush(stdout);
	return 0;
}
