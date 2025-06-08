# 基于 fuse 实现文件系统
fuse (用户空间文件系统)

```shell
gcc -Wall simple_fuse.c -o simple_fuse `pkg-config --cflags --libs fuse`

mkdir /tmp/fuse_mount_test
xmake run fuse_learn fuse3 /tmp/fuse_mount_test
umount /tmp/fuse_mount_test
```
