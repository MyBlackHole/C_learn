obj-m:=kmalloc_mm.o

CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL:=$(shell uname -r)
# LINUX_KERNEL_PATH:=/usr/src/linux-headers-$(LINUX_KERNEL)
# LINUX_KERNEL_PATH:=/lib/modules/$(LINUX_KERNEL)/build

ifneq ($(KDIR),)
	LINUX_KERNEL_PATH:=$(KDIR)
else
	LINUX_KERNEL_PATH:=/lib/modules/$(shell uname -r)/build/
endif

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
