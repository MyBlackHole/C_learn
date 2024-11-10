json_file_test-objs := kjson_main.o kjson_parser.o test.o
obj-m := json_file_test.o

ifneq ($(KDIR),)
	KDIR:=$(KDIR)
else
	KDIR:=/lib/modules/$(shell uname -r)/build/
endif

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	rm -v *.o *.ko

