# 
dup2所复制的文件描述符与原来的文件描述符共享各种文件状态
共享所有的锁定，读写位置和各项权限或flags等.
返回值：
若dup2调用成功则返回新的文件描述符，出错则返回-1.

在shell的重定向功能中，(输入重定向”<”和输出重定向”>”)就是通过调用dup或dup2函数对标准输入和标准输出的操作来实现的。


当调用 dup2（int oldfd，int newfd）之后
若 newfd 原来已经打开了一个文件
则先关闭这个文件
然后 newfd 和 oldfd 指向了相同的文件
若 newfd 原来没有打开一个文件
则 newfd 直接指向和 oldfd 指向相同的文件
oldfd 可以直接关闭，因为它已经被复制到 newfd 中
