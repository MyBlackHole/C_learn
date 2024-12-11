#ifndef BANDWIDTH_H
#define BANDWIDTH_H
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>

#define COPY_BUFLEN 16384

struct bwlimit {
	int state;
	size_t buflen;
	/* 所需速率(以 kbit/s 为单位)*/
	u_int64_t rate; /* desired rate in kbit/s */
	/* 阈值, 超过该阈值我们将检查计时器*/
	u_int64_t thresh; /* threshold after which we'll check timers */
	/* 上次计时器间隔内写入的量*/
	u_int64_t lamt; /* amount written in last timer interval */
	struct timeval bwstart, bwend;
};

void bandwidth_limit_init(struct bwlimit *, u_int64_t, size_t);
void bandwidth_reset_limit(struct bwlimit *, u_int64_t);
void bandwidth_limit(struct bwlimit *, size_t);

#endif /* BANDWIDTH_H */
