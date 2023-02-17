#include <signal.h>
#include <stdio.h>
#include <string.h>

void sig_handler(int signo) { printf("[%s]\n", strsignal(signo)); }

int main(void)
{
    /* ignoring the signal */
    signal(SIGTERM, SIG_IGN);
    raise(SIGTERM);

    signal(SIGPIPE, sig_handler);
    raise(SIGPIPE);
    printf("Exit main()\n");
}
