#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Line4 {
	uint8_t data[0];
	uint32_t x;
	uint32_t y;
} Line4;

int demo_struct4_main()
{
	Line4 line;

	printf("&line: %p\n", &line);
	printf("(&line) + 1: %p\n", (&line) + 1);
	printf("((char *)&line) + 1: %p\n", ((char *)&line) + 1);
	return EXIT_SUCCESS;
}

// xmake run grammar struct4
// &line: 0x7ffc919a8ee0
// (&line) + 1: 0x7ffc919a8ee8
// ((char *)&line) + 1: 0x7ffc919a8ee1
