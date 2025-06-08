#include "gcc_learn.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

static demo_t demos[] = {
	DEMO_MAIN_ITEM(FUNCTION),
	DEMO_MAIN_ITEM(attribute),
	DEMO_MAIN_ITEM(alias),
	DEMO_MAIN_ITEM(offsetof),
	DEMO_MAIN_ITEM(builtin_clz),
	DEMO_MAIN_ITEM(weak_alias),
	DEMO_MAIN_ITEM(attribute1),
	DEMO_MAIN_ITEM(destructor),
	DEMO_MAIN_ITEM(sync_fetch_and_add),
	DEMO_MAIN_ITEM(destructor1),
	DEMO_MAIN_ITEM(__GNUC__),
};

int main(int argc, char **argv)
{
	printf("start main\n");
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
