#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

int demo_while_time_main()
{
	time_t start_time = time(NULL);

	while (true) {
		start_time = time(NULL);
	}
	(void)start_time;

	return EXIT_SUCCESS;
}
