```shell
会互相等待锁，然后互相获取锁，最后释放锁。
如果获取到锁进程意外终止，则会一直等待锁，导致死锁。

❯ xmake run sys_mman_learn_mutex_sm_server
waiting mutex lock...
get mutex lock
release mutex lock
waiting mutex lock...
get mutex lock
release mutex lock
waiting mutex lock...

❯ xmake run sys_mman_learn_mutex_sm_client
wait lock
get lock
release lock
wait lock
get lock
^C
```
