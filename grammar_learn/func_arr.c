#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FUNC_NUM 10

int (*funcs[FUNC_NUM])();

int func1()
{
    printf("func1\n");
    return EXIT_SUCCESS;
}

int func2()
{
    printf("func2\n");
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    funcs[0] = func1;
    funcs[1] = func2;

    funcs[0]();
    funcs[1]();

    return EXIT_SUCCESS;
}
