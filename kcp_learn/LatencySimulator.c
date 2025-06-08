#include "LatencySimulator.h"
#include "DelayPacket.h"
#include "Random.h"
#include <stdlib.h>
#include <sys/time.h>
#include <tbox/container/element.h>
#include <tbox/container/vector.h>
#include <unistd.h>

/* get system time */
static inline void itimeofday(long *sec, long *usec)
{
#if defined(__unix)
	struct timeval time;
	gettimeofday(&time, NULL);
	if (sec)
		*sec = time.tv_sec;
	if (usec)
		*usec = time.tv_usec;
#else
	static long mode = 0, addsec = 0;
	BOOL retval;
	static IINT64 freq = 1;
	IINT64 qpc;
	if (mode == 0) {
		retval = QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
		freq = (freq == 0) ? 1 : freq;
		retval = QueryPerformanceCounter((LARGE_INTEGER *)&qpc);
		addsec = (long)time(NULL);
		addsec = addsec - (long)((qpc / freq) & 0x7fffffff);
		mode = 1;
	}
	retval = QueryPerformanceCounter((LARGE_INTEGER *)&qpc);
	retval = retval * 2;
	if (sec)
		*sec = (long)(qpc / freq) + addsec;
	if (usec)
		*usec = (long)((qpc % freq) * 1000000 / freq);
#endif
}

/* get clock in millisecond 64 */
static inline IINT64 iclock64(void)
{
	long s, u;
	IINT64 value;
	itimeofday(&s, &u);
	value = ((IINT64)s) * 1000 + (u / 1000);
	return value;
}

static inline IUINT32 iclock()
{
	return (IUINT32)(iclock64() & 0xfffffffful);
}

/* sleep in millisecond */
static inline void isleep(unsigned long millisecond)
{
#ifdef __unix /* usleep( time * 1000 ); */
	struct timespec ts;
	ts.tv_sec = (time_t)(millisecond / 1000);
	ts.tv_nsec = (long)((millisecond % 1000) * 1000000);
	/*nanosleep(&ts, NULL);*/
	usleep((millisecond << 10) - (millisecond << 4) - (millisecond << 3));
	(void)ts;
#elif defined(_WIN32)
	Sleep(millisecond);
#endif
}

// #define createLatencySimulator(lostrate, rttmin, rttmax, intnmax)  \
//   __createLatencySimulator(lostrate, rttmin, rttmax, nmax)

LatencySimulator *createLatencySimulator(int lostrate, int rttmin, int rttmax,
					 int nmax)
{
	struct LatencySimulator *latencySimulator = NULL;
	latencySimulator = malloc(sizeof(*latencySimulator));

	latencySimulator->current = iclock();
	latencySimulator->lostrate =
		lostrate / 2; // 上面数据是往返丢包率，单程除以2
	latencySimulator->rttmin = rttmin / 2;
	latencySimulator->rttmax = rttmax / 2;
	latencySimulator->nmax = nmax;
	latencySimulator->tx1 = latencySimulator->tx2 = 0;
	latencySimulator->p12 = tb_vector_init(0, tb_element_long());
	latencySimulator->p21 = tb_vector_init(0, tb_element_long());
	latencySimulator->r12 = createRandom(100);
	latencySimulator->r21 = createRandom(100);
	return latencySimulator;
}

void clearLatencySimulator(LatencySimulator *latencySimulator)
{
	tb_vector_clear(latencySimulator->p12);
	tb_vector_clear(latencySimulator->p21);
}

void sendLatencySimulator(LatencySimulator *latencySimulator, int peer,
			  const void *data, int size)
{
	if (peer == 0) {
		latencySimulator->tx1++;
		if (getRandom(latencySimulator->r12) <
		    latencySimulator->lostrate)
			return;
		if ((int)tb_vector_size(latencySimulator->p12) >=
		    latencySimulator->nmax)
			return;
	} else {
		latencySimulator->tx2++;
		if (getRandom(latencySimulator->r12) <
		    latencySimulator->lostrate)
			return;
		if ((int)tb_vector_size(latencySimulator->p21) >=
		    latencySimulator->nmax)
			return;
	}
	DelayPacket *pkt = createDelayPacket(size, data);
	latencySimulator->current = iclock();
	IUINT32 delay = latencySimulator->rttmin;
	if (latencySimulator->rttmax > latencySimulator->rttmin)
		delay += rand() %
			 (latencySimulator->rttmax - latencySimulator->rttmin);
	// 设置延迟时间
	delayPacketSetTs(pkt, latencySimulator->current + delay);
	// if (peer == 0) {
	//   p12.push_back(pkt);
	// } else {
	//   p21.push_back(pkt);
	// }
}

void destroyLatencySimulator(LatencySimulator *latencySimulator)
{
	if (!latencySimulator) {
		return;
	}

	if (latencySimulator->r12) {
		destroyRandom(latencySimulator->r12);
	}

	if (latencySimulator->r21) {
		destroyRandom(latencySimulator->r21);
	}

	if (latencySimulator->p12) {
		tb_vector_exit(latencySimulator->p12);
	}

	if (latencySimulator->p21) {
		tb_vector_exit(latencySimulator->p21);
	}

	free(latencySimulator);
}
