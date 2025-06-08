# sendfile

零拷贝支持

## 定义
```shell
#include<sys/sendfile.h>
ssize_t senfile(int out_fd,int in_fd,off_t* offset,size_t count);

in_fd 参数是待读出内容的文件描述符，out_fd 参数是待写入内容的文件描述符。
offset 参数指定从读入文件流的哪个位置开始读，如果为空，则使用读入文件流默认的起始位置。
count 参数指定文件描述符 in_fd 和 out_fd 之间传输的字节数。

in_fd 必须是一个支持类似 mmap 函数的文件描述符，即它必须指向真实的文件，
不能是socket和管道，
而out_fd必须是一个socket
```

