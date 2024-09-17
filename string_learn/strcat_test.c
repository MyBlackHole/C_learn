#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int demo_strcat_test_main()
{
	char *first_name = "Theo";
	char *last_name = "Tsao";
	char *name = (char *)malloc(strlen(first_name) + strlen(last_name));
	strcpy(name, first_name);
	strcat(name, last_name + 1);
	printf("%s\n", name);
	return 0;
}
