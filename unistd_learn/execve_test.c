#include <stdlib.h>
#include <unistd.h>


int demo_execve_main()
{
    char *argv[] = {"ls", "-al", "/etc/passwd", NULL};
    char *envp[] = {"PATH=/bin", NULL};
    execve("/bin/ls", argv, envp);
    return EXIT_SUCCESS;
}
