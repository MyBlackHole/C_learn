#include "unistd_learn.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

static demo_t demos[] = {
	DEMO_MAIN_ITEM(copy_file_range),
	DEMO_MAIN_ITEM(getcwd),
	DEMO_MAIN_ITEM(write),
	DEMO_MAIN_ITEM(write1),
	DEMO_MAIN_ITEM(unlink),
	DEMO_MAIN_ITEM(truncate),
	DEMO_MAIN_ITEM(ftruncate),
	DEMO_MAIN_ITEM(ftruncate1),
	DEMO_MAIN_ITEM(symlink),
	DEMO_MAIN_ITEM(chroot),
	DEMO_MAIN_ITEM(sysconf),
	DEMO_MAIN_ITEM(link),
	DEMO_MAIN_ITEM(access),
	DEMO_MAIN_ITEM(setsid),
	DEMO_MAIN_ITEM(pipe2),
	DEMO_MAIN_ITEM(pipe_2),
	DEMO_MAIN_ITEM(pipe_1),
	DEMO_MAIN_ITEM(read),
	DEMO_MAIN_ITEM(read1),
	DEMO_MAIN_ITEM(fork),
	DEMO_MAIN_ITEM(dup21),
	DEMO_MAIN_ITEM(pread_1),
	DEMO_MAIN_ITEM(getuid),
	DEMO_MAIN_ITEM(pwrite),
	DEMO_MAIN_ITEM(pwrite_io),
	DEMO_MAIN_ITEM(execve),
	DEMO_MAIN_ITEM(write3),
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
