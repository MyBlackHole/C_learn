#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void
abort(void)            /* POSIX-style abort() function */
{
    sigset_t mask;
    struct sigaction action;

    /* 调用者不能忽略SIGABRT，如果已重置为默认值 */
    sigaction(SIGABRT, NULL, &action);
    if (action.sa_handler == SIG_IGN) {
        action.sa_handler = SIG_DFL;
        sigaction(SIGABRT, &action, NULL);
    }
    if (action.sa_handler == SIG_DFL)
        fflush(NULL);            /* 冲洗所有打开的stdio流 */

    /* 呼叫者无法阻止SIGABRT；确保它不受阻碍 */
    sigfillset(&mask);
    sigdelset(&mask, SIGABRT);    /* 关闭 SIGABRT 信号 */
    sigprocmask(SIG_SETMASK, &mask, NULL);
    kill(getpid(), SIGABRT);    /* 发送信号 */

    /* 如果在这里，进程捕获了SIGABRT并返回 */
    fflush(NULL);                /* 如果在这里，进程捕获了SIGABRT并返回 */
    action.sa_handler = SIG_DFL;
    sigaction(SIGABRT, &action, NULL);    /* 重置为默认 */
    sigprocmask(SIG_SETMASK, &mask, NULL);    /* 确保 ... */
    kill(getpid(), SIGABRT);                /* and one more time */
    exit(1);    /* this should never be executed ... */
}
