```
extern int nanosleep (const struct timespec *__requested_time,
		      struct timespec *__remaining);
会被信号中断, 中断后剩余时间会赋值给 __remaining
```
