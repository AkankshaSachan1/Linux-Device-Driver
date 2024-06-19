obj-m := timer.o

KERNELDRIVER = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KERNELDRIVER) M=$(PWD) modules

clean:
	make -C $(KERNELDRIVER) M=$(PWD) clean
