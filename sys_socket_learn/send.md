send()函数只能在套接字处于连接状态的时候才能使用。（只有这样才知道接受者是谁）

send和write的唯一区别就是最后一个参数：flags的存在，当我们设置flags为0时，send和wirte是同等的。

即：

// 下面的两个函数等效：
write(sockfd,buf,le)；
send(sockfd,buf,len,0)；

当消息不适合套接字的发送缓冲区时，send通常会阻塞，除非套接字在事先设置为非阻塞的模式，那样他不会阻塞，而是返回EAGAIN或者EWOULDBLOCK错误，此时可以调用select函数来监视何时可以发送数据。

参数描述

ssize_t类型在之前的read/write中描述符哦，相当于long。

sockfd：接收消息的套接字的文件描述符。

buf：要发送的消息。

len：要发送的字节数。

flags：flags参数表示下列标志中的0个或多个

    MSG_CONFIRM ：用来告诉链路层，

    MSG_DONTROUTE：不要使用网关来发送数据，只发送到直接连接的主机上。通常只有诊断或者路由程序会使用，这只针对路由的协议族定义的，数据包的套接字没有。

    MSG_DONTWAIT ：启用非阻塞操作，如果操作阻塞，就返回EAGAIN或EWOULDBLOCK

    MSG_EOR ：当支持SOCK_SEQPACKET时，终止记录。

    MSG_MORE ：调用方有更多的数据要发送。这个标志与TCP或者udp套接字一起使用

    MSG_NOSIGNAL ：当另一端中断连接时，请求不向流定向套接字上的错误发送SIGPIPE ，EPIPE 错误仍然返回。

    MSG_OOB：在支持此概念的套接字上发送带外数据（例如，SOCK_STREAM类型）；底层协议还必须支持带外数据

返回值

在网络中的传递错误对send来说是无法检测的，能检测到某些发送错，则会返回-1；

否则返回发送的字节数。

EACCES (For  UNIX domain sockets, which are identified by pathname) Write permission is denied on the destination socket file, or search per‐
              mission is denied for one of the directories the path prefix.  (See path_resolution(7).)

       EAGAIN or EWOULDBLOCK
              The socket is marked nonblocking and the requested operation would block.  POSIX.1-2001 allows either error to be  returned  for  this
              case, and does not require these constants to have the same value, so a portable application should check for both possibilities.

       EBADF  An invalid descriptor was specified.

       ECONNRESET
              Connection reset by peer.

       EDESTADDRREQ
              The socket is not connection-mode, and no peer address is set.

       EFAULT An invalid user space address was specified for an argument.

       EINTR  A signal occurred before any data was transmitted; see signal(7).

       EINVAL Invalid argument passed.

       EISCONN
              The  connection-mode socket was connected already but a recipient was specified.  (Now either this error is returned, or the recipient
              specification is ignored.)

       EMSGSIZE
              The socket type requires that message be sent atomically, and the size of the message to be sent made this impossible.

       ENOBUFS
              The output queue for a network interface was full.  This generally indicates that the interface has stopped sending, but may be caused
              by transient congestion.  (Normally, this does not occur in Linux.  Packets are just silently dropped when a device queue overflows.)

       ENOMEM No memory available.

       ENOTCONN
              The socket is not connected, and no target has been given.

       ENOTSOCK
              The argument sockfd is not a socket.

       EOPNOTSUPP
              Some bit in the flags argument is inappropriate for the socket type.

       EPIPE  The  local  end  has  been  shut  down  on  a connection oriented socket.  In this case the p
