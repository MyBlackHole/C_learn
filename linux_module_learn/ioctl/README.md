# test
```shell
sudo dmesg -w

sudo insmod my_ioctl.ko

sudo ../../out/obj/ioctl_learn/app
open success
receive 1 data=1
receive 3 data=102


[300749.549118] misc regist succeed
[300841.270844] misc open
[300841.270879] cmd type=A       nr=0    dir=0   size=0
[300841.270882] CMD_TEST_0
[300841.270883] cmd type=A       nr=1    dir=2   size=4
[300841.270885] CMD_TEST_1
[300841.270897] cmd type=A       nr=2    dir=1   size=4
[300841.270898] CMD_TEST_2 date=99
[300841.270900] cmd type=A       nr=3    dir=3   size=4
[300841.270901] CMD_TEST_3 date=101
[300841.270915] misc file release
```
