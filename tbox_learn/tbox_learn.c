#include "tbox_learn.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

static demo_env_t demos[] = {
	DEMO_MAIN_ENV_ITEM(winch),	DEMO_MAIN_ENV_ITEM(vector),
	DEMO_MAIN_ENV_ITEM(vector_mem), DEMO_MAIN_ENV_ITEM(sort),
	DEMO_MAIN_ENV_ITEM(allocator),	DEMO_MAIN_ENV_ITEM(stream),
	DEMO_MAIN_ENV_ITEM(list),	DEMO_MAIN_ENV_ITEM(heap),
	DEMO_MAIN_ENV_ITEM(heap1),

};

int main(int argc, char **argv, char **env)
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
				ret_ok = demos[index].main(argc - 1, argv + 1,
							   env);
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
