#include "sys_time_learn.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

static demo_env_t demos[] = {
	DEMO_MAIN_ENV_ITEM(timeval),	   DEMO_MAIN_ENV_ITEM(timer1),
	DEMO_MAIN_ENV_ITEM(time),	   DEMO_MAIN_ENV_ITEM(localtime),
	DEMO_MAIN_ENV_ITEM(localtime1),	   DEMO_MAIN_ENV_ITEM(localtime2),
	DEMO_MAIN_ENV_ITEM(gettimeofday),  DEMO_MAIN_ENV_ITEM(gettimeofday1),
	DEMO_MAIN_ENV_ITEM(gettimeofday2), DEMO_MAIN_ENV_ITEM(clock_gettime),
	DEMO_MAIN_ENV_ITEM(gettimeofday3), DEMO_MAIN_ENV_ITEM(localtime_r),
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
