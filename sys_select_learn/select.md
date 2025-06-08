# select

作用：
select函数是用来监视一个或多个文件句柄的状态变化的，可阻塞也可不阻塞。

定义：
int select(int fd_max, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
fd_max：传入的监视文件描述符集合中最大的文件描述符数值 + 1，因为select是从0开始一直遍历到数值最大的标识符。
readfds：文件描述符集合，检查该组文件描述符的可读性。
writefds：文件描述符集合，检查该组文件描述符的可写性。
exceptfds：文件描述符集合，检查该组文件描述符的异常条件。
timeout:
```c
struct timeval {
	time_t tv_sec;     /* 秒 */
	time_t tv_usec;    /* 微秒 */
};
timeout的值为NULL，则将select()函数置为阻塞状态，当监视的文件描述符集合中的某一个描述符发生变化才会返回结果并向下执行。
timeout的值等于0，则将select()函数置为非阻塞状态，执行select()后立即返回，无论文件描述符是否发生变化。
timeout的值大于0，则将select()函数的超时时间设为这个值，在超时时间内阻塞，超时后返回结果。
```

```c
FD_ZERO(fd_set *fd);             /* 清空该组文件描述符集合 */
FD_CLR(inr fd,fd_set *fd);       /* 清除该组文件描述符集合中的指定文件描述符 */
FD_ISSET(int fd,fd_set *fd);     /* 测试指定的文件描述符是否在该文件描述符集合中 */
FD_SET(int fd,fd_set *fd);       /* 向该文件描述符集合中添加文件描述符 */
```

- 返回值：
-1：发生错误，并将所有描述符集合清0，可通过errno输出错误详情。
0：超时。
正数：发生变化的文件描述符数量。

<!-- 注意： -->
每次调用完select()函数后需要将文件描述符集合清空并重新设置，也就是设置的文件描述符集合是一次性使用的。
原因是调用完select()后文件描述符集合可能发生改变。
