#include <stdio.h>
#include <stdio.h>
#include <string.h>

int demo_hex_to_int_main()
{
	long int num = 0;
	printf("Enter a hex number: ");
	scanf("%lx", &num);
	printf("error: %ld.\n", num);
	printf("error str: %s.\n", strerror(-num));
	return 0;
}
