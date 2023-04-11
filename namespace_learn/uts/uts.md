# hostname 隔离测试
```c
#include <sched.h>
CLONE_NEWUTS
```
```shell
# 需要 root
sudo ./out/obj/namespace_learn/uts/uts
hostname
```
