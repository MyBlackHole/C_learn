# SPDX-License-Identifier: GPL-2.0

# needed for trace events
ccflags-y			+= -I$(src)

obj-$(CONFIG_BLK_DEV_NULL_BLK)	+= null_blk.o
null_blk-objs			:= main.o
ifeq ($(CONFIG_BLK_DEV_ZONED), y)
null_blk-$(CONFIG_TRACING) 	+= trace.o
endif
null_blk-$(CONFIG_BLK_DEV_ZONED) += zoned.o

CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL:=$(shell uname -r)
LINUX_KERNEL_PATH:=/lib/modules/${LINUX_KERNEL}/build/

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) KCFLAGS+=-DDEBUG modules
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean

