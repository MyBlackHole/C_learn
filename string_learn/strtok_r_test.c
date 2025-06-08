#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int demo_strtok_r_test_main(int argc, char **argv)
{
	char *item = NULL;
	char *data_tmp = NULL;

	if (argc < 2) {
		printf("Usage: %s substring\n", argv[0]);
		return EXIT_FAILURE;
	}

	item = strtok_r(argv[1], ";", &data_tmp);
	while (item != NULL) {
		printf("[%s]\n", item);
		item = strtok_r(NULL, ";", &data_tmp);
	}

	return 0;
}

// xmake run string_learn strstr_test lob
// Output:
// lobalView
// Found at position 7!
