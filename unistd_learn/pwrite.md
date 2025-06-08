``````
pwrite函数用于从打开文件的指定位置处写入指定字节的数据。函数原型如下：

#include <unistd.h>
ssize_t pwrite(int filedes, const void *buf, size_t nbytes, off_t offset);
返回值：若写入成功则返回实际写入的字节数，若出错则返回-1。
参数：

1、filedes文件标识符；

2、*buf要写入到文件的数据的缓冲区；

3、nbytes要写入的字节数；

4、offset文件指针。

pwrite相当于先调用lseek接着调用write。但又不完全是这样：

（1）pwrite是原子操作，定位和写操作在一个原子操作中完成，期间不可中断。但分开的lseek和write中间可能被其他程序中断。

（2）pwrite不更改当前文件的指针，也就是说不改变当前文件偏移量。

（3）pwrite中的offset是一个绝对量，相对于文件开始处的绝对量，与当前文件指针位置无关。
``````
