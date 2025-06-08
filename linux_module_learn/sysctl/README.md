# test
```shell
sudo dmesg -w

sudo insmod sysctl-kern.ko

# dmesg log
[6月24 19:18] sysctl register success.

❯ ls
abi  debug  dev  fs  kernel  net  sunrpc  user  vm
❯ ls
abi  debug  dev  fs  kernel  kernusr  net  sunrpc  user  vm
  /proc/sys                                                                                                            default pypy3.6-7.0.0 at  19:20:26
❯

sudo su

root@black:/proc/sys# ls
kernel/  kernusr

root@black:/proc/sys# echo 123 > kernusr


# dmesg log
[6月24 19:31] original value = 1024
[  +0.000009] this is write operation, current value = 123


root@black:/proc/sys# cat kernusr
123


# dmesg log
[6月24 19:33] original value = 123
[  +0.000041] original value = 123
```
