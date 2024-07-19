#include <stdio.h>
#include <string.h>

int demo_memset1_test_main()
{
	char str[50];

	strcpy(str, "This is string.h library function");
	puts(str);

	memset(str, '$', 7);
	puts(str);

	return (0);
}

/* out
 * This is string.h library function
 * $$$$$$$ string.h library function
 */
