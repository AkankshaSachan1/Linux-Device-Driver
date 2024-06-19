obj-m := chardriver.o

KERNDIR = /lib/modules/$(shell uname -r)/build 

all:
	make -C $(KERNDIR) M=$(PWD) modules
	gcc user.c -o user

clean:
	make -C $(KERNDIR) M=$(PWD) clean
	rm user