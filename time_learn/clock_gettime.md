```
int clock_gettime(clockid_t clk_id, struct timespec *tp);
// 得到当前的时间
// clk_id 设置获取的时间类型
// CLOCK_REALTIME:系统实时时间,随系统实时时间改变而改变,即从UTC1970-1-1 0:0:0开始计时,

// 中间时刻如果系统时间被用户改成其他,则对应的时间相应改变

// CLOCK_MONOTONIC:从系统启动这一刻起开始计时,不受系统时间被用户改变的影响
// CLOCK_PROCESS_CPUTIME_ID:本进程到当前代码系统CPU花费的时间
// CLOCK_THREAD_CPUTIME_ID:本线程到当前代码系统CPU花费的时间
```
