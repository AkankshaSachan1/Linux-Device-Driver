obj-m := driver.o

KERNDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KERNDIR) M=$(PWD) modules
	gcc write.c -o write
	gcc read.c -o read
	gcc ioctl.c -o ioctl

clean:
	make -C $(KERNDIR) M=$(PWD) clean
	rm read
	rm write
	rm ioctl