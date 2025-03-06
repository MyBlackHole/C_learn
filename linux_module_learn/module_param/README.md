# test
```shell

# insmod module_param_test.ko
[24303.867524] module_param_test: module license 'GPS' taints kernel.
[24303.870075] Disabling lock debugging due to kernel taint
[24303.873210] global_val_test = 9
[24303.874315] hello my world enter

# rmmod module_param_test.ko
[24322.782830] hello World exit

# insmod module_param_test.ko global_val_test=50
[24332.727804] global_val_test = 50
[24332.728878] hello world enter

cat /sys/module/module_param_test/parameters/global_val_test

# dmesg log
[519511.688956] global_val_test = 50
[519511.688963] hello world enter

❯ cat /sys/module/module_param_test/parameters/global_val_test
50

❯ sudo rmmod module_param_test

# dmesg log
[519665.492400] hello World exit

<!--同时还支持设置-->
echo 100 > /sys/module/module_param_test/parameters/global_val_test
```
