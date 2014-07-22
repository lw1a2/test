obj-m:=kernelmode_netlink.o

KERNEL_VERSION=$(shell uname -r)

all:
	make -C /lib/modules/$(KERNEL_VERSION)/build/ SUBDIRS=$(shell pwd) modules

install:
	make -C /lib/modules/$(KERNEL_VERSION)/build/ SUBDIRS=$(shell pwd) modules_install

clean:
	rm -f *.ko* *.mod* *.o  modules.order  Module.symvers

.PHONY: all clean install


