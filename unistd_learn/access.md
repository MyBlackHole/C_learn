```
在Linux下，access函数的声明在<unistd.h>文件中，声明如下：

int access(const char *pathname, int mode);
access函数用来判断指定的文件或目录是否存在(F_OK)，已存在的文件或目录是否有可读(R_OK)、可写(W_OK)、可执行(X_OK)权限。F_OK、R_OK、W_OK、X_OK这四种方式通过access函数中的第二个参数mode指定。如果指定的方式有效，则此函数返回0，否则返回-1。

可用于判断文件或者目录是否存在，
access()会检查是否可以读/写某一已存在的文件，access()只作权限的核查,
并不理会文件形态或文件内容，因此，如果一目录表示为"可写入"，表示可以在该目录中建立新文件等操作，而非意味此目录可以被当做文件处理

pathname为文件或文件夹的路径，当前目录直接使用文件或文件夹名；mode表示检查模式，共4种模式：

R_OK, 4 只判断是否有读权限，对应宏定义里面的00 只存在
W_OK, 2 只判断是否有写权限，对应宏定义里面的02 写权限
X_OK, 1 判断是否有执行权限，对应宏定义里面的04 读权限
F_OK, 0 只判断是否存在，对应宏定义里面的05 读和写权限
返回值
如果指定的存取方式有效，则函数返回0，否则函数返回-1
```
