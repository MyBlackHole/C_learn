/*
gcc changetitle.c -o changetitle
*/
#include <stdio.h>
#include <sys/prctl.h>

int main(int argc, char *argv[], char *envp[])
{
    char *new_name = "littlehann-program";

    getchar();
    prctl(PR_SET_NAME, new_name);
    getchar();

    return 0;
}
