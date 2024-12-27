#include "sys_socket_learn.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static demo_t demos[] = {
	DEMO_MAIN_ITEM(SO_RCVTIMEO),
	DEMO_MAIN_ITEM(SO_RCVTIMEO1),
	DEMO_MAIN_ITEM(SO_RCVTIMEO1_client),
	DEMO_MAIN_ITEM(sendmsg),
	DEMO_MAIN_ITEM(listen_fork),
	DEMO_MAIN_ITEM(listen_fork_exec),
	DEMO_MAIN_ITEM(listen),
	DEMO_MAIN_ITEM(shutdown),
	DEMO_MAIN_ITEM(AF_LOCAL),
	DEMO_MAIN_ITEM(connect),
	DEMO_MAIN_ITEM(accept),
	DEMO_MAIN_ITEM(socketpair),
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
