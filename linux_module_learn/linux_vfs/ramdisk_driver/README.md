1.compile:
	make
2.test:
	insmod ramdisk_driver.ko
	sudo mkfs.ext4 /dev/ram0
	mkdir /tmp/ramdisk
	mount /dev/myramdisk ./ramdisk/
	cd /tmp/ramdisk
3.result:
root@ubuntu:ramdisk# ls
lost+found
root@ubuntu:ramdisk# 
