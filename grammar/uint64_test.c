#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define BASE 10
#define OFFSET 32
#define LSNNUM 18

int demo_uint64_main(int argc, char *argv[])
{
	uint64_t lsn;
	int index = 1;
	int ret;
	char lsn_str[LSNNUM];

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <int>\n", argv[0]);
		return EXIT_FAILURE;
	}

	for (; index < argc; index++) {
		lsn = strtol(argv[index], (char **)NULL, BASE);
		ret = snprintf(lsn_str, sizeof(lsn_str), "%X/%X",
			       (uint32_t)(lsn >> OFFSET), (uint32_t)lsn);
		printf("ret = %d, lsn: %ld - %s\n", ret, lsn, lsn_str);
	}


	return EXIT_SUCCESS;
}
