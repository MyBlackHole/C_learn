obj-m:=log.o
CU_PATH:=$(shell pwd)
LINUX_KERNEL:=$(shell uname -r)
LK_PATH:=/lib/modules/$(LINUX_KERNEL)/build

all:
	make -C $(LK_PATH) M=$(CU_PATH) modules
clean:
	make -C $(LK_PATH) M=$(CU_PATH) clean
