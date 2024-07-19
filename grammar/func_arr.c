#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FUNC_NUM 10

int (*funcs[FUNC_NUM])();

extern int func1();

extern int func2();

int demo_func_main(int argc, char *argv[])
{
	funcs[0] = func1;
	funcs[1] = func2;

	funcs[0]();
	funcs[1]();

	return EXIT_SUCCESS;
}
