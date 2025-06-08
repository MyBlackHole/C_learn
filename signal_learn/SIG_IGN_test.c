#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

int demo_SIGTERM_main(void)
{
	/* ignoring the signal */
	// SIG_IGN, 忽略SIGTERM信号
	signal(SIGTERM, SIG_IGN);
	raise(SIGTERM);
	printf("Exit main()\n");
	return EXIT_SUCCESS;
}
