#include <argp.h>
#include <stdlib.h>

static char doc[] = "Black Hole";

static struct argp argp = { 0, 0, 0, doc };

int demo_argp_parse_1_main(int argc, char *argv[])
{
	argp_parse(&argp, argc, argv, 0, 0, 0);
	exit(0);
}
