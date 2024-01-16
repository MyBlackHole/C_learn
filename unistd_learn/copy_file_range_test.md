# file_file_range_test
将数据范围从一个文件复制到另一个文件

## 语法
```c
#define _GNU_SOURCE
#include <unistd.h>

ssize_t copy_file_range(int fd_in, loff_t *off_in,
                        int fd_out, loff_t *off_out,
                        size_t len, unsigned int flags);
```

## 说明
```shell
copy_file_range()系统调用在两个文件描述符之间执行内核内复制，而没有将数据从内核传输到用户空间然后再传输回内核的额外费用。它将最多len字节的数据从源文件描述符fd_in复制到目标文件描述符fd_out，覆盖目标文件请求范围内的任何数据。

以下语义适用于off_in，类似的语句适用于off_out：

*
如果off_in为NULL，则从文件偏移量开始从fd_in读取字节，并通过复制的字节数来调整文件偏移量。
*
如果off_in不为NULL，则off_in必须指向一个缓冲区，该缓冲区指定将从fd_in读取字节的起始偏移量。 fd_in的文件偏移不会更改，但是off_in会适当调整。
fd_in和fd_out可以引用同一文件。如果它们引用相同的文件，则不允许源和目标范围重叠。

提供flags参数以允许将来扩展，当前必须将其设置为0。
```

## 错误说明
```shell
EBADF
    一个或多个文件描述符无效。
EBADF
    fd_in不开放供阅读；或fd_out未打开以进行写入。
EBADF
    为文件描述符fd_out引用的打开文件描述(请参见open(2))设置O_APPEND标志。
EFBIG
    试图在超过内核支持的最大文件偏移量的位置写入。
EFBIG
    试图写一个超出允许的最大文件大小的范围。在文件系统实现之间，最大文件大小有所不同，并且可能与允许的最大文件偏移量不同。
EFBIG
    试图写超出进程的文件大小资源限制的文件。这也可能导致进程接收到SIGXFSZ信号。
EINVAL
    flags参数不为0。
EINVAL
    fd_in和fd_out引用相同的文件，并且源范围和目标范围重叠。
EINVAL
    fd_in或fd_out都不是常规文件。
EIO
    复制时发生低级I / O错误。
EISDIR
    fd_in或fd_out都引用目录。
ENOMEM
    内存不足。
ENOSPC
    目标文件系统上没有足够的空间来完成复制。
EOVERFLOW
    请求的源或目标范围太大，无法以指定的数据类型表示。
EPERM
    fd_out指的是一个不可变的文件。
ETXTBSY
    fd_in或fd_out都指向活动的交换文件。
EXDEV
    fd_in和fd_out引用的文件不在同一已挂载的文件系统上(Linux 5.3之前的版本)。
```
