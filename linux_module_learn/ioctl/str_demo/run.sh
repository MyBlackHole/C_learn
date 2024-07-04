make
gcc main.c -o main

sudo insmod ioctl_test.ko
sudo dmesg -w

sudo rmmod ioctl_test

❯ ls -alh /dev/ioctl_test
Permissions  Size User Date Modified Name
crw-------  236,0 root 12 Jun 11:07   /dev/ioctl_test

❯ ls -alh /sys/class/ioctl_test/ioctl_test/
Permissions Size User Date Modified Name
.r--r--r--  4.1k root 12 Jun 11:08   dev
drwxr-xr-x     - root 12 Jun 11:08   power
lrwxrwxrwx     - root 12 Jun 11:08   subsystem -> ../../../../class/ioctl_test
.rw-r--r--  4.1k root 12 Jun 11:08   uevent


sudo ./main
/dev/ioctl_test用户空间: width=20  high=210
please input>>>>>asdfasdf
