# ipc 隔离测试
```c
#include <sched.h>
CLONE_NEWIPC
```
```shell
# 创建队列
ipcmk -Q
# 查询新建的队列
ipcs -q
# 需要 root
sudo ./out/obj/namespace_learn/ipc/ipc
ipcs -q
```
