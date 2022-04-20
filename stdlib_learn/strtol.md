```
long int strtol(const char *str, char **endptr, int base)
参数
str -- 要转换为长整数的字符串。
endptr -- 对类型为 char* 的对象的引用，其值由函数设置为 str 中数值后的下一个字符。
base -- 基数，必须介于 2 和 36（包含）之间，或者是特殊值 0。
返回值
该函数返回转换后的长整数，如果没有执行有效的转换，则返回一个零值。
```
