#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[], const char *envp[])
{
	if (setenv("NEW_VAR", "new_value", 1) != 0) {
		perror("setenv");
		exit(EXIT_FAILURE);
	}

	if (envp != NULL) {
		for (size_t i = 0; envp[i] != NULL; ++i) {
			if (strcmp(envp[i], "NEW_VAR=new_value") == 0) {
				puts(envp[i]);
				goto END;
			}
		}
		printf("No such variable found!\n");
	}
END:

	exit(EXIT_SUCCESS);
}
