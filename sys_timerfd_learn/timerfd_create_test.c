#include <stdint.h>
#include <stdio.h>
#include <sys/timerfd.h>
#include <poll.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>

int demo_timerfd_create_main()
{
	// period timeout value = 1s
	// initial timeout value = 5s100ns
	struct itimerspec timebuf = { { 1, 0 }, { 5, 100 } };
	int timerfd =
		timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);

	timerfd_settime(timerfd, 0, &timebuf, NULL);

	struct pollfd fds[1];
	int len = sizeof(fds) / sizeof(fds[0]);
	fds[0].fd = timerfd;
	fds[0].events = POLLIN | POLLERR | POLLHUP;

	while (true) {
		int n = poll(fds, len, -1);
		for (int i = 0; i < len && n-- > 0; ++i) {
			if (fds[i].revents & POLLIN) {
				uint64_t val;
				int ret = read(timerfd, &val, sizeof(val));
				// ret should be 8
				if (ret != sizeof(val)) {
					perror("read");
					break;
				}
				printf("timerfd expired, val = %lld\n",
				       (long long)val);
			}
		}
	}
	close(timerfd);
	return 0;
}
