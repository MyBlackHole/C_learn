#include <stdio.h>
#include <sys/time.h>

/* 把目前的时间有tv 所指的结构返回，当地时区的信息则放到tz 所指的结构中 */
/* gettimeofday (struct timeval * tv, struct timezone * tz) */

/* timeval 结构定义为： */
/* struct timeval{ */
/*     long tv_sec;  //秒 */
/*     long tv_usec;  //微秒 */
/* }; */
/*  */
/* timezone 结构定义为： */
/* struct timezone */
/* { */
/*     int tz_minuteswest;  //和Greenwich 时间差了多少分钟 */
/*     int tz_dsttime;  //日光节约时间的状态 */
/* }; */

int main()
{
    struct timezone tz;
    struct timeval tv;

    gettimeofday(&tv, &tz);
    printf("tv_sec:%ld\n", tv.tv_sec);
    printf("tv_usec:%ld\n", tv.tv_usec);
    printf("tz_minuteswest:%d\n", tz.tz_minuteswest);
    printf("tz_dsttime:%d\n", tz.tz_dsttime);

    return 0;
}
