# configfs

```shell
mount -t configfs none /sys/kernel/config/
```

```shell
sudo insmod configfs_sample.ko
❯ ls -alh /sys/kernel/config/
Permissions Size User Date Modified Name
drwxr-xr-x     - root 13 Jul 06:32   01-childless
drwxr-xr-x     - root 13 Jul 06:32   02-simple-children
drwxr-xr-x     - root 13 Jul 06:32   03-group-children


❯ ls -alh /sys/kernel/config/03-group-children
Permissions Size User Date Modified Name
.r--r--r--  4.1k root 13 Jul 06:33   description
```

- 01
```shell
❯ ls -alh /sys/kernel/config/01-childless
Permissions Size User Date Modified Name
.r--r--r--  4.1k root 13 Jul 06:32   description
.r--r--r--  4.1k root 13 Jul 06:32   showme
.rw-r--r--  4.1k root 13 Jul 06:32   storeme


[root@archlinux configfs]# cat /sys/kernel/config/01-childless/showme
0
[root@archlinux configfs]# cat /sys/kernel/config/01-childless/description
[01-childless]

The childless subsystem is the simplest possible subsystem in
configfs.  It does not support the creation of child config_items.
It only has a few attributes.  In fact, it isn't much different
than a directory in /proc.

[root@archlinux configfs]# echo "2" > /sys/kernel/config/01-childless/storeme
[root@archlinux configfs]# cat /sys/kernel/config/01-childless/showme
2
```

- 02
```shell
❯ ls -alh /sys/kernel/config/02-simple-children
Permissions Size User Date Modified Name
.r--r--r--  4.1k root 13 Jul 06:33   description


[root@archlinux configfs]# cat /sys/kernel/config/02-simple-children/description
[02-simple-children]

This subsystem allows the creation of child config_items.  These
items have only one attribute that is readable and writeable.


[root@archlinux configfs]# mkdir /sys/kernel/config/02-simple-children/2/

[root@archlinux configfs]# ls -alh /sys/kernel/config/02-simple-children/2/
total 0
drwxr-xr-x 2 root root    0 Jul 13 06:51 .
drwxr-xr-x 3 root root    0 Jul 13 06:51 ..
-rw-r--r-- 1 root root 4.0K Jul 13 06:51 storeme
```

- 03
```shell
[root@archlinux configfs]# ls -alh /sys/kernel/config/03-group-children
total 0
drwxr-xr-x 2 root root    0 Jul 13 06:33 .
drwxr-xr-x 5 root root    0 Jul 13 06:32 ..
-r--r--r-- 1 root root 4.0K Jul 13 06:42 description


[root@archlinux configfs]# mkdir /sys/kernel/config/03-group-children/2

[root@archlinux configfs]# ls -alh /sys/kernel/config/03-group-children/
total 0
drwxr-xr-x 3 root root    0 Jul 13 06:56 .
drwxr-xr-x 5 root root    0 Jul 13 06:32 ..
drwxr-xr-x 2 root root    0 Jul 13 06:56 2
-r--r--r-- 1 root root 4.0K Jul 13 06:56 description

[root@archlinux configfs]# ls -alh /sys/kernel/config/03-group-children/2
total 0
drwxr-xr-x 2 root root    0 Jul 13 06:56 .
drwxr-xr-x 3 root root    0 Jul 13 06:56 ..
-r--r--r-- 1 root root 4.0K Jul 13 06:57 description

[root@archlinux configfs]# ls -alh /sys/kernel/config/03-group-children/2/3
total 0
drwxr-xr-x 2 root root    0 Jul 13 06:58 .
drwxr-xr-x 3 root root    0 Jul 13 06:58 ..
-rw-r--r-- 1 root root 4.0K Jul 13 06:58 storeme


<!-- 级联创建 -->
[root@archlinux configfs]# mkdir -p /sys/kernel/config/03-group-children/2/3

<!-- 级联删除 -->
[root@archlinux configfs]# rmdir -p /sys/kernel/config/03-group-children/2/3/
rmdir: failed to remove directory '/sys/kernel/config/03-group-children': Operation not permitted
[root@archlinux configfs]# ls /sys/kernel/config/03-group-children/
description
```
