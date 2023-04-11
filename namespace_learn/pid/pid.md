# pid 隔离测试
```c
#include <sched.h>
CLONE_NEWPID
```
```shell
# 需要 root
sudo ./out/obj/namespace_learn/pid/pid
getpid() == 1
```
