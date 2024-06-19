obj-m := driver.o

KERNDIR =/lib/modules/$(shell uname -r)/build

all:
	make -C $(KERNDIR) M=$(PWD) modules
	gcc add.c -o add
	gcc sub.c -o sub
	gcc mul.c -o mul
	gcc div.c -o div
	gcc read.c -o read

clean:
	make -C $(KERNDIR) M=$(PWD) clean
	rm add
	rm sub
	rm mul
	rm div
	rm read	