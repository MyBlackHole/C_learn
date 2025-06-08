obj-m:= livepatch-sample.o
# obj-$(CONFIG_SAMPLE_LIVEPATCH) += livepatch-sample.o
CURRENT_PATH:=$(shell pwd)
ifneq ($(KDIR),)
	LINUX_KERNEL_PATH:=$(KDIR)
else
	LINUX_KERNEL_PATH:=/lib/modules/$(shell uname -r)/build/
endif

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean

