``````
pread函数用于从打开文件的指定位置开始读取数据，函数原型如下：

#include <unistd.h>
ssize_t pread(int filedes, void *buf, size_t nbytes, off_t offset);

返回值：若读取成功则返回实际读到的字节数，若已到文件结尾则返回0，若出错则返回-1。
参数：

1、filedes文件标识符；

2、*buf存放读出数据的缓冲区；

3、nbytes要读取的字节数；

4、offset文件指针。

pread相当于先调用lseek接着调用read。但又不完全是这样：

（1）pread是原子操作，定位和读操作在一个原子操作中完成，期间不可中断。但分开的lseek和read中间可能被其他程序中断。

（2）pread不更改当前文件的指针，也就是说不改变当前文件偏移量。

（3）pread中的offset是一个绝对量，相对于文件开始处的绝对量，与当前文件指针位置无关(同时不影响 read 的文件偏移量)。
``````
