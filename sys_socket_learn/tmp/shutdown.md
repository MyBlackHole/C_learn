# shutdown
破坏了socket 链接
读的时候可能侦探到EOF结束符
写的时候可能会收到一个SIGPIPE信号
这个信号可能直到socket buffer被填充了才收到，shutdown有一个关闭方式的参数

shutdown 可以单向关闭
Close不可以
当多线程共享/调用同一个Socket时,Close只是会减1,直到减到0才会真正去关闭Socket

0 不能再读
#define SHUT_RD		SHUT_RD
1 不能再写
#define SHUT_WR		SHUT_WR
2 读写都不能
#define SHUT_RDWR	SHUT_RDWR

shutdown与socket描述符没有关系，即使调用shutdown(fd, SHUT_RDWR)也不会关闭fd，最终还需close(fd)

