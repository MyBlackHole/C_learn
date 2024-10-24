#include "bandwidth.h"

void monotime_ts(struct timespec *ts)
{
	struct timeval tv;
#if defined(HAVE_CLOCK_GETTIME) &&                              \
	(defined(CLOCK_BOOTTIME) || defined(CLOCK_MONOTONIC) || \
	 defined(CLOCK_REALTIME))
	static int gettime_failed = 0;

	if (!gettime_failed) {
#ifdef CLOCK_BOOTTIME
		if (clock_gettime(CLOCK_BOOTTIME, ts) == 0)
			return;
#endif /* CLOCK_BOOTTIME */
#ifdef CLOCK_MONOTONIC
		if (clock_gettime(CLOCK_MONOTONIC, ts) == 0)
			return;
#endif /* CLOCK_MONOTONIC */
#ifdef CLOCK_REALTIME
		/* Not monotonic, but we're almost out of options here. */
		if (clock_gettime(CLOCK_REALTIME, ts) == 0)
			return;
#endif /* CLOCK_REALTIME */
		fprintf(stderr, ("clock_gettime: %s", strerror(errno));
		gettime_failed = 1;
	}
#endif /* HAVE_CLOCK_GETTIME && (BOOTTIME || MONOTONIC || REALTIME) */
	gettimeofday(&tv, NULL);
	ts->tv_sec = tv.tv_sec;
	ts->tv_nsec = (long)tv.tv_usec * 1000;
}

void monotime_tv(struct timeval *tv)
{
	struct timespec ts;

	monotime_ts(&ts);
	tv->tv_sec = ts.tv_sec;
	tv->tv_usec = ts.tv_nsec / 1000;
}

void bandwidth_limit_init(struct bwlimit *bw, u_int64_t kbps, size_t buflen)
{
	bw->buflen = buflen;
	bw->rate = kbps;
	bw->thresh = buflen;
	bw->lamt = 0;
	bw->state = 0;
	timerclear(&bw->bwstart);
	timerclear(&bw->bwend);
}

void bandwidth_reset_limit(struct bwlimit *bw, u_int64_t kbps)
{
	bw->rate = kbps;
}

void bandwidth_limit(struct bwlimit *bw, size_t read_len)
{
	u_int64_t waitlen;
	struct timespec ts, rm;

	bw->lamt += read_len;
	if (!timerisset(&bw->bwstart)) {
		monotime_tv(&bw->bwstart);
		return;
	}
	if (bw->lamt < bw->thresh)
		return;

	monotime_tv(&bw->bwend);
	timersub(&bw->bwend, &bw->bwstart, &bw->bwend);
	if (!timerisset(&bw->bwend))
		return;

	bw->lamt *= 8;
	waitlen = (double)1000000L * bw->lamt / bw->rate;

	bw->bwstart.tv_sec = waitlen / 1000000L;
	bw->bwstart.tv_usec = waitlen % 1000000L;

	if (timercmp(&bw->bwstart, &bw->bwend, >)) {
		timersub(&bw->bwstart, &bw->bwend, &bw->bwend);

		/* Adjust the wait time */
		if (bw->bwend.tv_sec) {
			bw->thresh /= 2;
			if (bw->thresh < bw->buflen / 4)
				bw->thresh = bw->buflen / 4;
		} else if (bw->bwend.tv_usec < 10000) {
			bw->thresh *= 2;
			if (bw->thresh > bw->buflen * 8)
				bw->thresh = bw->buflen * 8;
		}

		TIMEVAL_TO_TIMESPEC(&bw->bwend, &ts);
		while (nanosleep(&ts, &rm) == -1) {
			if (errno != EINTR)
				break;
			ts = rm;
		}
	}

	bw->lamt = 0;
	monotime_tv(&bw->bwstart);
}
