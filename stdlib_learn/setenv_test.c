#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int main(int argc, const char *argv[], const char *envp[])
{
	printf("environ:  %p\n", environ);
	printf("envp:     %p\n", envp);

	setenv("NEW_VAR", "new_value", 1);

	puts("----Added NEW_VAR----");
	printf("environ:  %p\n", environ);
	printf("envp:     %p\n", envp);

	if (environ != NULL) {
		for (size_t i = 0; environ[i] != NULL; ++i) {
			if (strcmp(environ[i], "NEW_VAR=new_value") == 0) {
				puts(environ[i]);
				goto END;
			}
		}
		printf("No such variable found!\n");
	}

END:
	exit(EXIT_SUCCESS);
}
