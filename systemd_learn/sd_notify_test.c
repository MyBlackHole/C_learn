#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <systemd/sd-daemon.h>
#include <unistd.h>

#define INTERVAL 1000

int main()
{
	sd_notify(0, "READY=1");

	char *env;
	int interval = INTERVAL;
	int is_run = true;
	env = getenv("WATCHDOG_USEC");
	if (env) {
		// str to int
		interval = atoi(env) / (2 * 1000000);
	}
	sd_notify(0, "WATCHDOG=1");

	while (is_run) {
		sleep(interval);
		/* Way to ping systemd */
		sd_notify(0, "WATCHDOG=1");
	}
	return 0;
}
