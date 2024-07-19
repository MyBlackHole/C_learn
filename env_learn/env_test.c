#include <stdio.h>

int demo_env_test_main(int argc, char **argv, char **env)
{
	while (env && *env) {
		printf("%s\n", *env);
		++env;
	}
	return 0;
}
