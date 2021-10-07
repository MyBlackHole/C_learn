//
// Created by Black Hole on 2020/11/26.
//

#include "apue.h"
#include <setjmp.h>


static void sig_alrm(int);

static jmp_buf env_alrm;

int
main() {
    int n, m;
    char line[MAXLINE];
    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
        err_sys("signal(SIGALRM) error");
    if ((m = setjmp(env_alrm)) != 0) {
        write(STDOUT_FILENO, (char *) &m, 2);
        err_quit(" read timeout ");
    }
    alarm(10);
    if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
        err_sys("read error");
    alarm(0);
    write(STDOUT_FILENO, line, n);
    exit(0);
}

static void
sig_alrm(int aigno) {
    longjmp(env_alrm, 69);
}