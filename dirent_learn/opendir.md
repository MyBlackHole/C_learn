```
函数说明
用于判断目录是否存在，opendir()用来打开参数name 指定的目录, 并返回DIR*形态的目录流, 和open()类似, 接下来对目录的读取和搜索都要使用此返回值。opendir可用于判断目录是否存在，但是调用以后需要使用closedir()关闭目录流，否则会有内存泄漏

返回值
成功则返回DIR* 型态的目录流, 打开失败则返回NULL，错误代码存于errno（需要include <errno.h>）

使用示例
#include <dirent.h>
int file_exist(const char *path)
{
    if ((dp = opendir(path)) == NULL)
    {
        return 0;
    }
    else
    {
        closedir(dp);
        return 1;
    }
}


/*
错误代码：
1、EACCESS 权限不足。
2、EMFILE 已达到进程可同时打开的文件数上限。
3、ENFILE 已达到系统可同时打开的文件数上限。
4、ENOTDIR 参数name 非真正的目录。
5、ENOENT 参数name 指定的目录不存在, 或是参数name 为一空字符串。
6、ENOMEM 核心内存不足。
*/
```
