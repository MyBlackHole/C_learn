sudo dmesg -w
sudo insmod sysfs_demo.ko

# [347712.101600] sysfs_init

ls /sys/kernel/sysfs_demo/
fs_file

sudo su
# root
echo `pwd` >> /sys/kernel/sysfs_demo/fs_file/add_file

