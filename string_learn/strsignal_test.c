#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sig_handler(int signo)
{
	printf("[%s]\n", strsignal(signo));
}

int demo_strsignal_test_main(void)
{
	/* ignoring the signal */
	signal(SIGTERM, SIG_IGN);
	raise(SIGTERM);

	signal(SIGPIPE, sig_handler);
	raise(SIGPIPE);
	printf("Exit main()\n");
	return EXIT_SUCCESS;
}
