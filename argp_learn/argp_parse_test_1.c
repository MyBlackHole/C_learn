#include <argp.h>
#include <stdlib.h>

const char *argp_program_version = "argp_parse_test 1";
const char *argp_program_bug_address = "1358244533@qq.com";

static char doc[] = "Black Hole";

static struct argp argp = {0, 0, 0, doc};

int main(int argc, char *argv[]) {
  argp_parse(&argp, argc, argv, 0, 0, 0);
  exit(0);
}
