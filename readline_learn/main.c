#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	using_history();
	char *str;

	while (1) {
		str = readline("输入:");
		if (strcmp(str, "q") == 0) {
			break;
		}

		add_history(str);
	}
	return EXIT_SUCCESS;
}
