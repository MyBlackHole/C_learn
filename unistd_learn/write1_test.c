#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int demo_write1_main(void)
{
	putchar('a');
	write(STDOUT_FILENO, "b", 1);
	putchar('a');
	write(STDOUT_FILENO, "b", 1);
	putchar('a');
	write(STDOUT_FILENO, "b", 1);

	printf("\n");
	return EXIT_SUCCESS;
}
// window 下生成ababab
// linux下是bbbaaa
