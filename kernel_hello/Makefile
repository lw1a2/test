obj-m:=hello.o

all:
	make -C /lib/modules/2.6.32-279.5.2.el6.x86_64/build SUBDIRS=$(shell pwd) modules

install:
	make -C /lib/modules/2.6.32-279.5.2.el6.x86_64/build SUBDIRS=$(shell pwd) modules_install

clean:
	rm -rf *.ko *.o *.mod.* .H* .tm* .*cmd Module.symvers *.unsigned *.order

.PHONY: clean all install

