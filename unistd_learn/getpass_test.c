#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int demo_getpass_main(int argc, char *argv[])
{
	char *input;

	input = getpass("intput:");
	fprintf(stdout, "p %s", input);
	return EXIT_SUCCESS;
}
