obj-m := spin_driver.o

KERNDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KERNDIR) M=$(PWD) modules
	gcc wr_1.c -o wr1
	gcc wr_2.c -o wr2
	gcc rd.c -o rd

clean:
	make -C $(KERNDIR) M=$(PWD) clean
	rm wr1
	rm wr2
	rm rd