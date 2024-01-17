# splice

## 函数原型
```shell
#include <fcntl.h>
ssize_t splice(int fd_in, loff_t *off_in, int fd_out, loff_t *off_out, size_t len, unsigned int flags);

fd_in 参数是待输入描述符。如果它是一个管道文件描述符，则 off_in 必须设置为NULL；
否则 off_in 表示从输入数据流的何处开始读取，此时若为NULL，则从输入数据流的当前偏移位置读入。

fd_out / off_out 与上述相同，不过是用于输出。
len参数指定移动数据的长度。
flags参数则控制数据如何移动：
    SPLICE_F_NONBLOCK：splice 操作不会被阻塞。然而，如果文件描述符没有被设置为不可被阻塞方式的 I/O ，那么调用 splice 有可能仍然被阻塞。
    SPLICE_F_MORE：告知操作系统内核下一个 splice 系统调用将会有更多的数据传来。
    SPLICE_F_MOVE：如果输出是文件，这个值则会使得操作系统内核尝试从输入管道缓冲区直接将数据读入到输出地址空间，这个数据传输过程没有任何数据拷贝操作发生。

使用splice时， fd_in和fd_out中必须至少有一个是管道文件描述符。

调用成功时返回移动的字节
```
