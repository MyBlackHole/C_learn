# unlink

unlink()函数功能即为删除文件。执行unlink()函数会删除所给参数指定的文件。

注意：
    执行unlink()函数并不一定会真正的删除文件，
    它先会检查文件系统中此文件的连接数是否为1，
    如果不是1说明此文件还有其他链接对象，
    因此只对此文件的连接数进行减1操作。
    若连接数为1，并且在此时没有任何进程打开该文件，此内容才会真正地被删除掉。
    在有进程打开此文件的情况下，则暂时不会删除，直到所有打开该文件的进程都结束时文件就会被删除。

返回值：成功返回0，失败返回 -1
