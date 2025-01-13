#include "fcntl_learn.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

static demo_t demos[] = {
	DEMO_MAIN_ITEM(splice),	    DEMO_MAIN_ITEM(splice1),
	DEMO_MAIN_ITEM(open),	    DEMO_MAIN_ITEM(open1),
	DEMO_MAIN_ITEM(file_flags), DEMO_MAIN_ITEM(fcntl),
	DEMO_MAIN_ITEM(F_WRLCK),    DEMO_MAIN_ITEM(creat),
	DEMO_MAIN_ITEM(fallocate),  DEMO_MAIN_ITEM(FD_CLOEXEC),
	DEMO_MAIN_ITEM(SSH1),	    DEMO_MAIN_ITEM(O_CLOEXEC),
	DEMO_MAIN_ITEM(SSH2),	    DEMO_MAIN_ITEM(open_3),
	DEMO_MAIN_ITEM(open_4),	    DEMO_MAIN_ITEM(open_5),
	DEMO_MAIN_ITEM(open_6),
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
