# 文件系统
```shell
# 加载模块到内核
sudo insmod myfs.ko

# 查看内核日志缓存区
sudo dmesg -w

# 查看模块列表
lsmod | grep myfs

# 卸载模块
sudo rmmod myfs

cat /proc/filesystems
nodev   myfs

mkdir /tmp/my_fs/
mount -t myfs none /tmp/my_fs/
```
