#include "pthread_learn.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

static demo_t demos[] = {
	DEMO_MAIN_ITEM(setname_np),
	DEMO_MAIN_ITEM(create4),
	DEMO_MAIN_ITEM(create3),
	DEMO_MAIN_ITEM(pthread_setschedparam),
	DEMO_MAIN_ITEM(self),
	DEMO_MAIN_ITEM(once),
	DEMO_MAIN_ITEM(mutex_unlock),
	DEMO_MAIN_ITEM(rwlock1),
	DEMO_MAIN_ITEM(rwlock2),
	DEMO_MAIN_ITEM(pthread_cancel),
	DEMO_MAIN_ITEM(rwlock3),
	DEMO_MAIN_ITEM(pthread_attr_setinheritsched),
	DEMO_MAIN_ITEM(setspecific),
	DEMO_MAIN_ITEM(getspecific),
	DEMO_MAIN_ITEM(pthread_mutex_consistent),
	DEMO_MAIN_ITEM(create5),
	DEMO_MAIN_ITEM(test_thread_ftruncate_write),
	DEMO_MAIN_ITEM(pthread_key_t),
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
