# configfs

```shell
# 安装(载入)
sudo modprobe configfs_sample.ko
# 或
sudo insmod configfs_sample.ko
ls -l /sys/kernel/config/
01-childless
02-simple-children
03-group-children

# 卸载
sudo modprobe -r configfs_sample.ko
```
