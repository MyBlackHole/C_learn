#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FUNC_NUM 10

static int (*funcs[FUNC_NUM])();

static int func1()
{
	printf("This is func1.\n");
	return 0;
}

static int func2()
{
	printf("This is func2.\n");
	return 0;
}

int demo_func_main(int argc, char *argv[])
{
	funcs[0] = func1;
	funcs[1] = func2;

	funcs[0]();
	funcs[1]();

	return EXIT_SUCCESS;
}
