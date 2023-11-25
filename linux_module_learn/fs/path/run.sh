make
sudo insmod path_test.ko

# [28982.331527] path_init: init called
# [28982.331543] path dentry test: lookup path, d_iname: path_test.c

sudo rmmod path_test
# [29825.684220] path_exit: exit called


sudo insmod path_test.ko
# [29958.364831] path dentry test: lookup path, d_iname: path_test.c
# [29958.364834] path dentry test: pathname:
