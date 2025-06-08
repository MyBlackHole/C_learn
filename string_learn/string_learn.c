#include "string_learn.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static demo_t demos[] = {
	DEMO_MAIN_ITEM(memchr_test),   DEMO_MAIN_ITEM(memcmp_test),
	DEMO_MAIN_ITEM(memcpy_test),   DEMO_MAIN_ITEM(memmove_test),
	DEMO_MAIN_ITEM(memset1_test),  DEMO_MAIN_ITEM(memset_test),
	DEMO_MAIN_ITEM(strcat_test),   DEMO_MAIN_ITEM(strchr_test),
	DEMO_MAIN_ITEM(strcmp_test),   DEMO_MAIN_ITEM(strcoll_test),
	DEMO_MAIN_ITEM(strcpy_test),   DEMO_MAIN_ITEM(strdup_test),
	DEMO_MAIN_ITEM(strerror_test), DEMO_MAIN_ITEM(strlen_test),
	DEMO_MAIN_ITEM(strncmp_test),  DEMO_MAIN_ITEM(strncpy_test),
	DEMO_MAIN_ITEM(strrchr_test),  DEMO_MAIN_ITEM(strsignal_test),
	DEMO_MAIN_ITEM(strstr_test),   DEMO_MAIN_ITEM(strtok_test),
	DEMO_MAIN_ITEM(strncmp1_test), DEMO_MAIN_ITEM(path_splice),
	DEMO_MAIN_ITEM(strncmp_3),     DEMO_MAIN_ITEM(strlcpy_test),
	DEMO_MAIN_ITEM(memcpy_1),      DEMO_MAIN_ITEM(strtok_r_test),

};
int main(int argc, char **argv)
{
	// find the main func from the first argument
	int ret_ok = 0;
	char const *name = NULL;
	size_t num = arrayn(demos);
	if (argc > 1 && argv[1]) {
		size_t index = 0;
		for (index = 0; index < num; index++) {
			// find it?
			if (demos[index].name &&
			    !strcmp(demos[index].name, argv[1])) {
				// save name
				name = demos[index].name;

				// done main
				ret_ok = demos[index].main(argc - 1, argv + 1);
				break;
			}
		}
	}

	// no this demo? help it
	if (!name) {
		// walk name
		size_t index = 0;
		for (index = 0; index < num; index++) {
			printf("testname: %s\n", demos[index].name);
		}
	}

	// ok?
	return ret_ok;
}
