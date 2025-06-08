#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*typedef struct Line3 {*/
/*	uint8_t data[0];*/
/*	uint32_t x;*/
/*	uint32_t y;*/
/*} Line3;*/
typedef struct Line3 {
	union {
		uint8_t data[8];
		struct {
			uint32_t x;
			uint32_t y;
		};
	};
} Line3;

int demo_struct3_main()
{
	Line3 line;
	int length = 100;
	int line_byte_length = sizeof(line);

	printf("%d\n", line_byte_length);

	Line3 *line_ref = (struct Line3 *)malloc(sizeof(struct Line3) + length);
	line_ref->x = length;
	line_ref->y = length;
	for (int index = 0; index < line_byte_length; index++) {
		printf("data[%d]:8: %b\n", index, line_ref->data[index]);
	}

	printf("data[0]:32: %d\n", line_ref->data[0]);
	printf("data[4]:32: %d\n", line_ref->data[4]);
	printf("data[0]:64: %lx\n", *((uint64_t *)line_ref->data));
	return EXIT_SUCCESS;
}

// ❯ xmake run grammar struct3
// 8
// data[0]:8: 1100100
// data[1]:8: 0
// data[2]:8: 0
// data[3]:8: 0
// data[4]:8: 1100100
// data[5]:8: 0
// data[6]:8: 0
// data[7]:8: 0
// data[0]:32: 100
// data[4]:32: 100
// data[0]:64: 6400000064
