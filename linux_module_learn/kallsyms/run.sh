cd ./hello2/
make
sudo insmod hello2.ko

# [ 8737.666409] hello2_init: init called



cd ./hello/
make
sudo insmod hello.ko


# [10102.587564] hello_init: init called
# [10102.640344] found KKK_test_func = 00000000dc75de3e
# [10102.640359] FUNC: KKK_test_func called, flag=0
