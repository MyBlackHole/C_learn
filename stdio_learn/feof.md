```
描述
C 库函数 int feof(FILE *stream) 测试给定流 stream 的文件结束标识符。

声明
下面是 feof() 函数的声明。

int feof(FILE *stream)
参数
stream -- 这是指向 FILE 对象的指针，该 FILE 对象标识了流。
返回值
当设置了与流关联的文件结束标识符时，该函数返回一个非零值，否则返回零。

文件结束符号（EOF）是 win(CTRL+Z)|linux(CTRL+D)
```
