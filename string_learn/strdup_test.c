#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int demo_strdup_test_main()
{
	char str[] = "strdup";
	char *str_dup;
	str_dup = strdup(str);
	printf("b[]=\"%s\"\n", str_dup);
	return EXIT_SUCCESS;
}
