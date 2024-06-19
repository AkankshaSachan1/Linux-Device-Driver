obj-m := driver.o

KERNDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KERNDIR) M=$(PWD) modules
	gcc write.c -o write
	gcc read.c -o read

clean:
	make -C $(KERNDIR) M=$(PWD) clean
	rm read
	rm write
	