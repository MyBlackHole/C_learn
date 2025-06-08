#include "grammar.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static demo_t demos[] = {
	DEMO_MAIN_ITEM(pg_summary),
	DEMO_MAIN_ITEM(test1),
	DEMO_MAIN_ITEM(test),
	DEMO_MAIN_ITEM(bool),
	DEMO_MAIN_ITEM(argv_test),
	DEMO_MAIN_ITEM(do_while),
	DEMO_MAIN_ITEM(VA_ARGS),
	DEMO_MAIN_ITEM(sizeof),
	DEMO_MAIN_ITEM(int),
	DEMO_MAIN_ITEM(uint64),
	DEMO_MAIN_ITEM(continue),
	DEMO_MAIN_ITEM(wrs),
	DEMO_MAIN_ITEM(cleanup),
	DEMO_MAIN_ITEM(enum),
	DEMO_MAIN_ITEM(union),
	DEMO_MAIN_ITEM(const),
	DEMO_MAIN_ITEM(define),
	DEMO_MAIN_ITEM(define1),
	DEMO_MAIN_ITEM(typedef),
	DEMO_MAIN_ITEM(hex_to_int),
	DEMO_MAIN_ITEM(uint64_1),
	DEMO_MAIN_ITEM(while),
	DEMO_MAIN_ITEM(while_malloc),
	DEMO_MAIN_ITEM(while_time),
	DEMO_MAIN_ITEM(uint64_2),
	DEMO_MAIN_ITEM(uint16_t),
	DEMO_MAIN_ITEM(read_file_by_semicolon),
	DEMO_MAIN_ITEM(disassemble),
	DEMO_MAIN_ITEM(log_test),
	DEMO_MAIN_ITEM(test2),

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
