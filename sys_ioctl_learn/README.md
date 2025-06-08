# ioctl

在应用层调用 ioctl 函数时，内核会调用对应驱动 fd file_operations 中的 ublocked_ioctl 函数

kernel module 例子:
 ../linux_module_learn/ioctl/

user app:
app.c
