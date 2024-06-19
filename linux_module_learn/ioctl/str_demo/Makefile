obj-m:= ioctl_test.o
CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL:=$(shell uname -r)
# LINUX_KERNEL_PATH:=/usr/src/linux-headers-$(LINUX_KERNEL)
LINUX_KERNEL_PATH:=/lib/modules/$(LINUX_KERNEL)/build

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) KCFLAGS+=-DDEBUG modules
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean

