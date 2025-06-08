# idr

系统许多资源都用整数 ID 来标识，
如进程 ID、文件描述符 ID、IPC ID 等；
资源信息通常存放在对应的数据结构中 (如进程信息存放在task_struct中、ipc 信息存放在ipc_perm中)，
id 与数据结构的关联机制有不同的实现，IDR 机制是其中的一种。

IDR，ID Radix 的缩写。
IDR 主要用于建立 id 与指针(指向对应的数据结构) 之间的 对应关系。
IDR 用类基数树结构来构造一个稀疏数组，以 id 为索引找到对应数组元素， 进而找到对应的数据结构指针。
用到 IDR 机制的主要有：IPC id (消息队列 id、 信号量 id、共享内存 id 等)，磁盘分区 id (sda 中数字部分）等。

## linux
Linux内核提供了一套完整的 IDR 实现机制，其基于Radix-tree

## test
```shell
sudo insmod idr_test.ko
[15929.600497] idr_test: loading out-of-tree module taints kernel.
[15929.600502] idr_test: module verification failed: signature and/or required key missing - tainting kernel
[15929.601093] t's ID is 0
[15929.601094] o's ID is 1
[15929.601095] o's ID is 2
[15929.601096] s's ID is 3
[15929.601097] m's ID is 4
[15929.601098] a's ID is 5
[15929.601098] l's ID is 6
[15929.601099] l's ID is 7
[15929.601100] w's ID is 8
[15929.601101] o's ID is 9
[15929.601102] r's ID is 10
[15929.601103] d's ID is 11
[15929.601104] o's ID is 0
[15929.601105] o's ID is 1
[15929.601106] o's ID is 2
[15929.601107] s's ID is 3
[15929.601108] m's ID is 4
[15929.601108] a's ID is 5
[15929.601109] l's ID is 6
[15929.601110] 7 is not used
[15929.601111] w's ID is 8
[15929.601112] o's ID is 9
[15929.601112] r's ID is 10
[15929.601113] d's ID is 11
[15929.601114] o's ID is 0
[15929.601115] o's ID is 1
[15929.601116] o's ID is 2
[15929.601117] s's ID is 3
[15929.601117] m's ID is 4
[15929.601118] a's ID is 5
[15929.601119] l's ID is 6
[15929.601120] w's ID is 8
[15929.601121] o's ID is 9
[15929.601122] r's ID is 10
[15929.601122] d's ID is 11

# 卸载
sudo rmmod idr_test
```


