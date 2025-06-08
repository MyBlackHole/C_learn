#include "stdio_learn.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

static demo_t demos[] = {
	DEMO_MAIN_ITEM(vsnprintf),  DEMO_MAIN_ITEM(args),
	DEMO_MAIN_ITEM(sprintf),    DEMO_MAIN_ITEM(ungetc),
	DEMO_MAIN_ITEM(tmpfile),    DEMO_MAIN_ITEM(stderr),
	DEMO_MAIN_ITEM(sprintf),    DEMO_MAIN_ITEM(snprintf),
	DEMO_MAIN_ITEM(scanf),	    DEMO_MAIN_ITEM(putchar),
	DEMO_MAIN_ITEM(putc),	    DEMO_MAIN_ITEM(print_time),
	DEMO_MAIN_ITEM(print_test), DEMO_MAIN_ITEM(hexTostr),
	DEMO_MAIN_ITEM(getline),    DEMO_MAIN_ITEM(getchar),
	DEMO_MAIN_ITEM(getc),	    DEMO_MAIN_ITEM(fwrite),
	DEMO_MAIN_ITEM(fseek),	    DEMO_MAIN_ITEM(fread),
	DEMO_MAIN_ITEM(fopen),	    DEMO_MAIN_ITEM(fopen1),
	DEMO_MAIN_ITEM(fileno),	    DEMO_MAIN_ITEM(fileno1),
	DEMO_MAIN_ITEM(fgets),	    DEMO_MAIN_ITEM(fgets1),
	DEMO_MAIN_ITEM(fgetc),	    DEMO_MAIN_ITEM(fflush),
	DEMO_MAIN_ITEM(feof),	    DEMO_MAIN_ITEM(fdopen),
	DEMO_MAIN_ITEM(fdopen1),    DEMO_MAIN_ITEM(buf_test),
	DEMO_MAIN_ITEM(renameat2),  DEMO_MAIN_ITEM(popen),
	DEMO_MAIN_ITEM(popen_w),    DEMO_MAIN_ITEM(popen_close),
	DEMO_MAIN_ITEM(rename),
	DEMO_MAIN_ITEM(setvbuf),

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
