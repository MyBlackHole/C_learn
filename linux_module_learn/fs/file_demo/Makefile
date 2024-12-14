obj-m += file_demo.o
 
CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL:=$(shell uname -r)

ifneq ($(KDIR),)
	LINUX_KERNEL_PATH:=$(KDIR)
else
	LINUX_KERNEL_PATH:=/lib/modules/$(shell uname -r)/build/
endif

# CONFIG_MODULE_SIG=n

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean

