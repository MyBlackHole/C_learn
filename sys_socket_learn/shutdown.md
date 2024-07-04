# shutdown
破坏了socket 链接
读的时候可能侦探到 EOF 结束符
写的时候可能会收到一个 SIGPIPE 信号
这个信号可能直到 socket buffer 被填充了才收到，shutdown 有一个关闭方式的参数

shutdown 可以单向关闭
shutdown(fd, SHUT_RD) 只能关闭读
shutdown(fd, SHUT_WR) 只能关闭写
shutdown(fd, SHUT_RDWR) 关闭读写

close 不可以
当多线程共享/调用同一个 socket 时, close 只是会减 1,直到减到 0 才会真正去关闭 socket

0 不能再读
#define SHUT_RD		SHUT_RD
1 不能再写
#define SHUT_WR		SHUT_WR
2 读写都不能
#define SHUT_RDWR	SHUT_RDWR

shutdown 与 socket 描述符没有关系，即使调用 shutdown(fd, SHUT_RDWR) 也不会关闭 fd，最终还需 close(fd)

