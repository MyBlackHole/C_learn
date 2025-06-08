#include <netinet/in.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define PORT 1000

int demo_htons_test_main(int argc, char *argv[])
{
	uint16_t ret;
	ret = htons(PORT);
	printf("%x\n", ret);
	return EXIT_SUCCESS;
}
