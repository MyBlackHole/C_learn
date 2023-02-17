#include <argp.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    argp_parse(0, argc, argv, 0, 0, 0);
    return 0;
}
