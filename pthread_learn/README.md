# rwlock

``````
初始化一个读写锁 pthread_rwlock_init
读锁定读写锁      pthread_rwlock_rdlock
非阻塞读锁定　　pthread_rwlock_tryrdlock
写锁定读写锁      pthread_rwlock_wrlock
非阻塞写锁定      pthread_rwlock_trywrlock
解锁读写锁         pthread_rwlock_unlock
释放读写锁         pthread_rwlock_destroy
``````

```shell
pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM); //设置内核级的线程,以获取较高的响应速度
//创建线程
ret = pthread_create(&iAcceptThreadId, &attr, AcceptThread, NULL);
```
