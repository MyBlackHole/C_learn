```
#include <unistd.h>
int gethostname(char *name, size_t len);
参数说明:
这个函数需要两个参数:
  接收缓冲区name,其长度必须为len字节或是更长，存获得的主机名。
  接收缓冲区name的最大长度:
返回值:
  如果函数成功，则返回0。如果发生错误则返回-1.错误号存放在外部变量errno中。


```
