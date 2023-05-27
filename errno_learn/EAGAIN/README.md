# EAGAIN
"Resource temporarily unavailable"是对应于 的错误消息，这意味着该操作将被阻止，但请求了非阻塞操作。对于 
这可能是由于以下任何一项：EAGAIN send()

使用显式将文件描述符标记为非阻塞或 fcntl()
将标志传递给 ;或MSG_DONTWAIT send()
使用套接字选项设置发送超时。SO_SNDTIMEO
