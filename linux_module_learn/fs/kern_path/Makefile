PWD = $(shell pwd)
KVERS =$(shell uname -r)
obj-m += kern_path.o
 
ifneq ($(KDIR),)
	LINUX_KERNEL_PATH:=$(KDIR)
else
	LINUX_KERNEL_PATH:=/lib/modules/$(shell uname -r)/build/
endif
 
kernel_modules:
	make -C $(LINUX_KERNEL_PATH) M=$(PWD) modules
 
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(PWD) clean
