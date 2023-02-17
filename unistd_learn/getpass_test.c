#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *input;

    input = getpass("intput:");
    fprintf(stdout, "p %s", input);
    return 0;
}
