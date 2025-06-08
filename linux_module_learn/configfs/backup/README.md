# configfs

```shell
mount -t configfs none /sys/kernel/config/
```


- 03
```shell
[root@archlinux configfs]# ls -alh /sys/kernel/config/backup
total 0
drwxr-xr-x 2 root root    0 Jul 13 06:33 .
drwxr-xr-x 5 root root    0 Jul 13 06:32 ..
-r--r--r-- 1 root root 4.0K Jul 13 06:42 description


[root@archlinux configfs]# mkdir /sys/kernel/config/backup/2

[root@archlinux configfs]# ls -alh /sys/kernel/config/backup/
total 0
drwxr-xr-x 3 root root    0 Jul 13 06:56 .
drwxr-xr-x 5 root root    0 Jul 13 06:32 ..
drwxr-xr-x 2 root root    0 Jul 13 06:56 2
-r--r--r-- 1 root root 4.0K Jul 13 06:56 description

[root@archlinux configfs]# ls -alh /sys/kernel/config/backup/2
total 0
drwxr-xr-x 2 root root    0 Jul 13 06:56 .
drwxr-xr-x 3 root root    0 Jul 13 06:56 ..
-r--r--r-- 1 root root 4.0K Jul 13 06:57 description

[root@archlinux configfs]# ls -alh /sys/kernel/config/backup/2/3
total 0
drwxr-xr-x 2 root root    0 Jul 13 06:58 .
drwxr-xr-x 3 root root    0 Jul 13 06:58 ..
-rw-r--r-- 1 root root 4.0K Jul 13 06:58 storeme


<!-- 级联创建 -->
[root@archlinux configfs]# mkdir -p /sys/kernel/config/backup/2/3

<!-- 级联删除 -->
[root@archlinux configfs]# rmdir -p /sys/kernel/config/backup/2/3/
rmdir: failed to remove directory '/sys/kernel/config/backup': Operation not permitted
[root@archlinux configfs]# ls /sys/kernel/config/backup/
description
```
