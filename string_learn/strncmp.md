```
描述
C 库函数 int strncmp(const char *str1, const char *str2, size_t n) 把 str1 和 str2 进行比较，最多比较前 n 个字节。

声明
下面是 strncmp() 函数的声明。

int strncmp(const char *str1, const char *str2, size_t n)
参数
str1 -- 要进行比较的第一个字符串。
str2 -- 要进行比较的第二个字符串。
n -- 要比较的最大字符数。
返回值
该函数返回值如下：

如果返回值 < 0，则表示 str1 小于 str2。
如果返回值 > 0，则表示 str1 大于 str2。
如果返回值 = 0，则表示 str1 等于 str2。
```
