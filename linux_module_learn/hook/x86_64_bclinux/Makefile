obj-m:=hook-demo.o
hook-demo-objs := demo.o utils/path.o imp/hook_api.o
ifneq ($(KDIR),)
	KDIR:=$(KDIR)
else
	KDIR:=/lib/modules/$(shell uname -r)/build/
endif

PWD := $(shell pwd)

EXTRA_CFLAGS += -I.
# EXTRA_CFLAGS += -I. -O0

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
