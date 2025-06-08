#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int demo_execve_main(int argc, char *argv[])
{
	// char *argv[] = { "ls", "-al", "/etc/passwd", NULL };
	char **argv_tmp = argv + 2;
	char *envp[] = { "PATH=/bin", NULL };
	printf("execve(%s, %p, %p)\n", argv[1], argv_tmp, envp);
	return execve(argv[1], argv_tmp, envp);
}

// out:
// xmake run unistd_learn execve /bin/pwd
// xmake run unistd_learn execve /bin/sleep sleep 100
