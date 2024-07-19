#include <argp.h>
#include <stdlib.h>

int demo_argp_parse_main(int argc, char *argv[])
{
	argp_parse(0, argc, argv, 0, 0, 0);
	return 0;
}
