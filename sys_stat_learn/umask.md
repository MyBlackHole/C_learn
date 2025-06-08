```
此函数的主要作用是在创建文件时设置或者屏蔽掉文件的一些权限。一般与open()函数配合使用。

umask(设置建立新文件时的权限遮罩)

相关函数 creat, open

表头文件:sys/types.h

sys/stat.h

定义函数: mode_t umask(mode_t mask);

函数说明:umask() 会将系统 umask 值设成参数 mask&0777 后的值，然后将先前的 umask 值返回。

在使用 open() 建立新文件时，该参数 mode 并非真正建立文件的权限，而是(mode&~umask)的权限值。例如，在建立文件时指定文件权限为 0666,通常 umask 值默认为 022,则该文件的真正权限则为 0666&~022=0644,也就是rw-r-r--。
```
