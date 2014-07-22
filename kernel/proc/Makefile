obj-m:=test_proc.o

KERNEL_VERSION=$(shell uname -r)

all:
	make -C /lib/modules/$(KERNEL_VERSION)/build SUBDIRS=$(shell pwd) modules

install:
	make -C /lib/modules/$(KERNEL_VERSION)/build SUBDIRS=$(shell pwd) modules_install

clean:
	rm -rf *.ko *.o *.mod.* .H* .tm* .*cmd Module.symvers *.unsigned *.order

.PHONY: clean all install

