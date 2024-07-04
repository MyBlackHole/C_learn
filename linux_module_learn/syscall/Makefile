obj-m:=my_syscall.o
PWD:= $(shell pwd)
KERNELDIR:= /lib/modules/$(shell uname -r)/build
KERNELDIR:= /run/media/black/Data/Documents/linux_debug/linux-4.19.315

EXTRA_CFLAGS= -O0

all:
	make -C $(KERNELDIR)  M=$(PWD) modules
clean:
	make -C $(KERNELDIR) M=$(PWD) clean
