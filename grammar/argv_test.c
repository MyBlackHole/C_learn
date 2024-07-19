#include <stdio.h>
#include <stdlib.h>

int demo_argv_test_main(int argc, char *argv[])
{
	int index;

	for (index = 0; index < argc;
	     index++) { /* echo all command-line args */
		printf("argv[%d]: %s\n", index, argv[index]);
	}
	exit(0);
}
