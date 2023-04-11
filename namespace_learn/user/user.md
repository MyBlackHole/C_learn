# user 隔离测试
```c
#include <sched.h>
CLONE_NEWUSER
```
```shell
sudo ./out/obj/namespace_learn/pid/pid
getpid() == 1
```
