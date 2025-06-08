#include <stdio.h>
#include <stdlib.h>

#include "test.h"

void print(void)
{
	printf("%s\n", "test main");
	return;
}

int main(int argc, char *argv[])
{
	printf("test start\n");
	Test();
	printf("test end\n");
	return 0;
}
