# fcntl

## 原型
```c
#include<unistd.h>
#include<fcntl.h>
int fcntl(int fd, int cmd);
int fcntl(int fd, int cmd, long arg);
int fcntl(int fd, int cmd ,struct flock* lock);
```

### cmd
F_DUPFD		复制文件描述符
F_GETFD	无	获取文件描述符标签
F_SETFD		设置文件描述符标签
F_GETFL		获取文件状态标签
F_SETFL		设置文件状态标签
F_GETFLK		获取文件锁
F_SETFLK		设置文件锁
F_SETLKW		类似F_SETLK，但等待完成
F_GETOWN		获取收到SIGIO信号的进程或进程组ID
F_SETOWN		设置接收SIGIO信号的进程或进程组ID
