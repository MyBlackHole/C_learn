```
描述
C 库函数 int strcmp(const char *str1, const char *str2) 把 str1 所指向的字符串和 str2 所指向的字符串进行自左向右逐个字符比较。

声明
下面是 strcmp() 函数的声明。

int strcmp(const char *str1, const char *str2)
参数
str1 -- 要进行比较的第一个字符串。
str2 -- 要进行比较的第二个字符串。
返回值
该函数返回值如下：

如果返回值小于 0，则表示 str1 小于 str2。
如果返回值大于 0，则表示 str1 大于 str2。
如果返回值等于 0，则表示 str1 等于 str2。


两个字符串自左向右逐个字符相比（按 ASCII值大小相比较），直到出现不同的字符或遇 \0 为止
```
