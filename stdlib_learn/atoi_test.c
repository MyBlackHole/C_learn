#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char s[] = "123456";
	fprintf(stdout, "%d\n", atoi(s));
	exit(0);
}
