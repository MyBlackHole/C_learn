obj-m:= write.o
CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL:=$(shell uname -r)
LINUX_KERNEL_PATH:=/lib/modules/$(LINUX_KERNEL)/build

# LINUX_KERNEL_PATH:=/run/media/black/Data/Documents/linux_debug/linux-4.19.315/

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
