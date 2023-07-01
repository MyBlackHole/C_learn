# test
```shell
sudo dmesg -w

sudo insmod module_param_test.ko global_val_test=50

cat /sys/module/module_param_test/parameters/global_val_test

# dmesg log
[519511.688956] global_val_test = 50
[519511.688963] hello world enter

❯ cat /sys/module/module_param_test/parameters/global_val_test
50

❯ sudo rmmod module_param_test

# dmesg log
[519665.492400] hello World exit
```
