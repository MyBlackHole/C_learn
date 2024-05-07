cd ./AAAA/
make

# 需要先编译，原因未知
cd ./BBBB/ 
make

cp ./AAAA/Module.symvers ./BBBB

cd ./BBBB/
make
# 必须 EXPORT_SYMBOL 才可以被其他模块调用


# 测试多个 mod 同名静态对象,使用问题
insmod AAAA.ko
insmod CCCC.ko
# 结论允许的, 非同一模块的同名静态对象可以共存

