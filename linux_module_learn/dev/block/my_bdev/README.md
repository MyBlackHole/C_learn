# 文件系统
[源连接](https://www.cnblogs.com/wangzahngjun/p/5365310.html)

```shell
# 加载模块到内核
sudo insmod bdev_test.ko

# 查看内核日志缓存区
sudo dmesg -w

# 查看模块列表
lsmod | grep bdev_test

# 卸载模块
sudo rmmod bdev_test

# 查看系统设备文件
ls /sys/devices/ltp_block_dev/
power  result  tcase  uevent
```
