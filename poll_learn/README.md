# poll

(来源)[https://blog.csdn.net/skypeng57/article/details/82743681]

成功时，poll() 返回结构体中 revents 域不为 0 的文件描述符个数；如果在超时前没有任何事件发生，poll()返回 0；

失败时，poll() 返回 -1，并设置 errno 为下列值之一：
    EBADF：一个或多个结构体中指定的文件描述符无效。
    EFAULT：fds 指针指向的地址超出进程的地址空间。
    EINTR：请求的事件之前产生一个信号，调用可以重新发起。
    EINVAL：nfds 参数超出 PLIMIT_NOFILE 值。
    ENOMEM：可用内存不足，无法完成请求。
