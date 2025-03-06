obj-m:=module_param_test.o

CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL:=$(shell uname -r)

ifneq ($(KDIR),)
	LINUX_KERNEL_PATH:=$(KDIR)
else
	LINUX_KERNEL_PATH:=/lib/modules/$(shell uname -r)/build/
endif

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules  #编译模块
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean   #清理
