#include "signal_learn.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

static demo_t demos[] = {
	DEMO_MAIN_ITEM(sigwait),
	DEMO_MAIN_ITEM(sigsuspend),
	DEMO_MAIN_ITEM(sigprocmask),
	DEMO_MAIN_ITEM(signal5),
	DEMO_MAIN_ITEM(signal4),
	DEMO_MAIN_ITEM(signal3),
	DEMO_MAIN_ITEM(signal2),
	DEMO_MAIN_ITEM(signal1),
	DEMO_MAIN_ITEM(SIGKILL),
	DEMO_MAIN_ITEM(SIGFPE),
	DEMO_MAIN_ITEM(sigemptyset),
	DEMO_MAIN_ITEM(sigaction),
	DEMO_MAIN_ITEM(sigaction1),
	DEMO_MAIN_ITEM(SIGTERM),
	DEMO_MAIN_ITEM(raise),
	DEMO_MAIN_ITEM(kill),

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
