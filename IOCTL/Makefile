obj-m := driver.o

KDIR=/lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(PWD) modules
	gcc user.c -o user
	
clean:
	make -C $(KDIR) M=$(PWD) clean
	rm user
