1.Description of design:
  a.the max len of filename is 64 byte.
  b.excpt super block, we can have 64 files.
  c.every block size is 512 byte.
2.compile:
	cd /mnt/rlk_basic/chapter_14/lab4
	make
3.test:
	insmod simplefs.ko
	cd /
	mkdir test_fs
	mount -t simple_fs none ./test_fs/
	cd test_fs
4.result:

root@ubuntu:test_fs# mkdir a
root@ubuntu:test_fs# ls
a
root@ubuntu:test_fs# cd a
root@ubuntu:a# 
root@ubuntu:a# 
root@ubuntu:a# echo 12345 > 111.txt
root@ubuntu:a# cat 111.txt 
12345
root@ubuntu:a# 
root@ubuntu:a# cd ..
root@ubuntu:test_fs# rm -rf a
root@ubuntu:test_fs# ls
