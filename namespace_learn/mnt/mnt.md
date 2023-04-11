# mnt 隔离测试
```c
#include <sched.h>
CLONE_NEWNS
```
```shell
# 需要 root
sudo ./out/obj/namespace_learn/mnt/mnt
# 挂载 /proc/
system("mount -t proc proc /proc")
```
