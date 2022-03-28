```
在Linux下，access函数的声明在<unistd.h>文件中，声明如下：

int access(const char *pathname, int mode);
access函数用来判断指定的文件或目录是否存在(F_OK)，已存在的文件或目录是否有可读(R_OK)、可写(W_OK)、可执行(X_OK)权限。F_OK、R_OK、W_OK、X_OK这四种方式通过access函数中的第二个参数mode指定。如果指定的方式有效，则此函数返回0，否则返回-1。
```
