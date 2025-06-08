#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

size_t cpu_count()
{
	static size_t ncpu = -1;
	if (ncpu == -1) {
		size_t count = sysconf(_SC_NPROCESSORS_ONLN);
		if (!count)
			count = sysconf(_SC_NPROCESSORS_CONF);
		if (!count)
			count = 1;
		ncpu = count;
	}
	return ncpu;
}

int demo_sysconf_main(int argc, char *argv[])
{
	printf("Number of processors: %zu\n", cpu_count());
	return EXIT_SUCCESS;
}
