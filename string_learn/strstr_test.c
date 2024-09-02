#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int demo_strstr_test_main(int argc, char **argv)
{
	char *str = "GoldenGlobalView";
	char *str2;

	if (argc < 2) {
		printf("Usage: %s substring\n", argv[0]);
		return EXIT_FAILURE;
	}

	str2 = strstr(str, argv[1]);
	if (str2) {
		printf("%s\n", str2);
		if (str2 == str) {
			printf("Found at the beginning of the string!\n");
		} else {
			printf("Found at position %ld!\n", str2 - str);
		}
	} else {
		printf("NotFound!\n");
	}

	return 0;
}

// xmake run string_learn strstr_test lob
// Output:
// lobalView
// Found at position 7!
