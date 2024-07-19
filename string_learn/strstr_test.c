#include <stdio.h>
#include <string.h>

int demo_strstr_test_main()
{
	char *str = "GoldenGlobalView";
	char *str1 = "lob";
	char *str2;
	str2 = strstr(str, str1);
	if (str2) {
		printf("%s\n", str2);
	} else {
		printf("NotFound!\n");
	}

	return 0;
}
