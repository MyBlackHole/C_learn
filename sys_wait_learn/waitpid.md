```
extern __pid_t waitpid (__pid_t __pid, int *__stat_loc, int __options);
__pid:
    > 0 等待进程id等于pid的子进程退出
    = -1 等待任意子进程退出
    = 0 等待本进程组任意子进程退出, 子进程加入其他进程组的不理睬
    < -1 等待指定进程组的任意子进程, 进程组id等于pid的绝对值
__stat_loc:
    保存子进程退出状态信息
__options:
    WNOHANG 如果指定pid的子进程没有结束，则函数立即返回0，不堵塞；如果结束则返回改子进程的进程号；
    WUNTRACED 如果子进程进入暂停状态立马返回

WIFEXITED(__stat_loc)  等.....
```
