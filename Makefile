.PHONY: test

obj-m := intercept.o
KDIR := /lib/modules/`uname -r`/build
PWD := `pwd`

all:
	make -C $(KDIR) M=$(PWD) modules
	gcc test.c -o test

install:
	sudo dmesg -c
	sudo insmod intercept.ko
	sudo ./test 1

uninstall:
	sudo ./test 4
	sudo rmmod intercept

test:
	sudo dmesg -C
	sudo insmod intercept.ko
	sudo ./test
	sudo rmmod intercept
	dmesg

clean: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

