#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#ifndef TIOCGWINSZ
#include <sys/ioctl.h>
#endif

static void pr_winsize(int fd)
{
	struct winsize size;

	if (ioctl(fd, TIOCGWINSZ, (char *)&size) < 0) {
		perror("TIOCGWINSZ error");
	}
	printf("%d rows, %d columns\n", size.ws_row, size.ws_col);
}

static void sig_winch(int signo)
{
	printf("SIGWINCH received\n");
	pr_winsize(STDIN_FILENO);
}

int demo_winch_main(void)
{
	if (isatty(STDIN_FILENO) == 0) {
		exit(EXIT_FAILURE);
	}
	if (signal(SIGWINCH, sig_winch) == SIG_ERR) {
		perror("signal error");
	}
	pr_winsize(STDIN_FILENO); /* print initial size */
	for (;;) /* and sleep forever */
	{
		pause();
	}
	// ntohll
}
