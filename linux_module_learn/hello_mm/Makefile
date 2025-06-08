obj-m:= hello_mm.o
CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL:=$(shell uname -r)
# LINUX_KERNEL_PATH:=/lib/modules/$(LINUX_KERNEL)/build

ifneq ($(KDIR),)
	LINUX_KERNEL_PATH:=$(KDIR)
else
	LINUX_KERNEL_PATH:=/lib/modules/$(shell uname -r)/build/
endif

ccflags-y=-O0

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
