```
包含头文件
#include <netdb.h>
#include <sys/socket.h>
 
函数原型:
struct hostent *gethostbyname(const char *name);
这个函数的传入值是域名或者主机名，例如"www.google.cn"等等。传出值，是一个hostent的结构。如果函数调用失败，将返回NULL。
返回hostent结构体类型指针:
struct hostent {
    char *h_name;   /* official name of host */
    char **h_aliases;  /*alias list */
    int h_addrtype;  /* host address type */
    int h_length; /* length of address */
    char **h_addr_list;   /* list of addresses*/
}
#define h_addr h_addr_list[0] /* for backward compatibility */


 hostent->h_name

   表示的是主机的规范名。例如www.google.com的规范名其实是www.l.google.com.

 hostent->h_aliases

    表示的是主机的别名www.google.com就是google他自己的别名。有的时候，有的主机可能有好几个别名，这些，其实都是为了易于用户记忆而为自己的网站多取的名字。

  hostent->h_addrtype

    表示的是主机ip地址的类型，到底是ipv4(AF_INET),还是ipv6(AF_INET6)

  hostent->h_length

    表示的是主机ip地址的长度

  hostent->h_addr_list

    表示的是主机的ip地址，注意，这个是网络字节存储的。千万不要直接用printf带%s参数来打这个东西，会有问题的哇。所以到真正需要打印出这个IP的话，需要调用inet_ntop()。

  const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);

    这个函数，是将类型为af的网络地址结构src,转换为主机序的字符串形式，存放在长度为cnt的字符串中。返回指向dst的一个指针。如果函数调用错误，返回值是NULL。
```
