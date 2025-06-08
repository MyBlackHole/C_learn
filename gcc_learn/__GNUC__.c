#include <stdio.h>

int demo___GNUC___main(int argc, char **argv)
{
	printf("%d\n", __GNUC__);
	printf("%d\n", __GNUC_MINOR__);
	printf("%d\n", __GNUC_PATCHLEVEL__);
	return 0;
}
