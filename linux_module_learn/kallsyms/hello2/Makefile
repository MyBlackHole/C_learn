#hello2_Makefile
PWD = $(shell pwd)
KVERS =$(shell uname -r)
KERNDIR =/lib/modules/${KVERS}/build/
 
obj-m += hello2.o
 
build: kernel_modules
 
kernel_modules:
	make -C $(KERNDIR) M=$(PWD) modules
 
clean:
	make -C $(KERNDIR) M=$(PWD) clean
