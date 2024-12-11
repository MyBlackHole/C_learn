make

#  通过 `modname` 制定待卸载驱动的信息
sudo insmod force_rmmod.ko modname=hello
#  查看是否加载成功, `exit` 函数是否正常替换
dmesg | tail -l
#  卸载 `hello` 驱动
sudo rmmod hello
#  卸载 `force_rmmod` 驱动
sudo rmmod force_rmmod


# [10042.899623] [before] name:hello, state:1, refcnt:1
# [10042.899631] No modules depond on hello...
# [10042.899633] [after] name:hello, state:0, refcnt:0
# [10059.020356] hello_exit: exit called
# [10065.500156] =======name : force_rmmod, state : 2 EXIT=======
#
#
#  通过 `modname` 制定待卸载驱动的信息
sudo insmod force_rmmod.ko modname=fsbackup
#  查看是否加载成功, `exit` 函数是否正常替换
dmesg | tail -l
#  卸载 `none_exit` 驱动
sudo rmmod none_exit
#  卸载 `force_rmmod` 驱动
sudo rmmod force_rmmod
