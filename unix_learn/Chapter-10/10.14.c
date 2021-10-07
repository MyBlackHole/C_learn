//
// Created by Black Hole on 2020/11/28.
//

#include "apue.h"
#include <errno.h>

void
func(int signo) {
    pr_mask("test:");
    printf("\nfunc: %p", func);
}

int
main() {
    if (signal(SIGALRM, func) < 0)
        err_sys("signal init error");
    alarm(1);
    pause();
    exit(0);
}