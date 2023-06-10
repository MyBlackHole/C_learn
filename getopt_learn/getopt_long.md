# getopt_long

```c
#include <unistd.h>  
extern char *optarg;  
extern int optind, opterr, optopt;  
#include <getopt.h>
int getopt(int argc, char * const argv[],const char *optstring);  
int getopt_long(int argc, char * const argv[], const char *optstring, const struct option *longopts, int *longindex);  
int getopt_long_only(int argc, char * const argv[], const char *optstring, const struct option *longopts, int *longindex);
```

1. argc 和argv 和main函数的两个参数一致
2. optstring: 表示短选项字符串
    形式如“a:b::cd:“，分别表示程序支持的命令行短选项有-a、-b、-c、-d

    1. 只有一个字符，不带冒号——只表示选项， 如-c 
    2. 一个字符，后接一个冒号——表示选项后面带一个参数，如-a 100
    3. 一个字符，后接两个冒号——表示选项后面带一个可选参数，即参数可有可无， 如果带参数，则选项与参数直接不能有空格
3. longopts：表示长选项结构体
```c
struct option 
{  
     const char *name;  
     int         has_arg;  
     int        *flag;  
     int         val;  
};  
eg:
 static struct option longOpts[] = {
      { "daemon", no_argument, NULL, 'D' },
      { "dir", required_argument, NULL, 'd' },
      { "out", required_argument, NULL, 'o' },
      { "log", required_argument, NULL, 'l' },
      { "split", required_argument, NULL, 's' },
      { "http-proxy", required_argument, &lopt, 1 },
      { "http-user", required_argument, &lopt, 2 },
      { "http-passwd", required_argument, &lopt, 3 },
      { "http-proxy-user", required_argument, &lopt, 4 },
      { "http-proxy-passwd", required_argument, &lopt, 5 },
      { "http-auth-scheme", required_argument, &lopt, 6 },
      { "version", no_argument, NULL, 'v' },
      { "help", no_argument, NULL, 'h' },
      { 0, 0, 0, 0 }
    };
```

    1. name:表示选项的名称,比如daemon,dir,out等。
    2. has_arg:表示选项后面是否携带参数。该参数有三个不同值，如下：
        a:  no_argument(或者是0)时   ——参数后面不跟参数值，eg: --version,--help
        b: required_argument(或者是1)时 ——参数输入格式为：--参数 值 或者 --参数=值。eg:--dir=/home
        c: optional_argument(或者是2)时  ——参数输入格式只能为：--参数=值
    3. flag:这个参数有两个意思，空或者非空。
        a:如果参数为空NULL，那么当选中某个长选项的时候，getopt_long将返回val值。
                eg，可执行程序 --help，getopt_long的返回值为h.             
        b:如果参数不为空，那么当选中某个长选项的时候，getopt_long将返回0，并且将flag指针参数指向val值。
                eg: 可执行程序 --http-proxy=127.0.0.1:80 那么getopt_long返回值为0，并且lopt值为1。
    4. val：表示指定函数找到该选项时的返回值，或者当flag非空时指定flag指向的数据的值val。
