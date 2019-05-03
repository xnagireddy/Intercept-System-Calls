.PHONY: test

obj-m := intercept.o
KDIR := /lib/modules/`uname -r`/build
PWD := `pwd`

all:
	make -C $(KDIR) M=$(PWD) modules
	gcc test.c -o test

test:
	sudo dmesg -C
	sudo insmod intercept.ko
	sudo ./test
	sudo rmmod intercept
	dmesg

clean: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

