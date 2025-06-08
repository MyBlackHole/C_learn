#include <stdio.h>
#include <strings.h>

int main(int argc, char *argv[])
{
	int status = 0;
	char *s1 = "abc";
	char *s2 = "abc";
	status = strcasecmp(s1, s2);
	printf("status: %d\n", status);
	return 0;
}
