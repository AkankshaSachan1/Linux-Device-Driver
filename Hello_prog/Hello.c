//include header files

#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

//Module initialization

static int hello_init(void)
{
    printk(KERN_INFO "INITIALIZING THE DEVICE DRIVER\n");
int i;
    for(i=0;i<10;i++){
        printk("HELLO BHAI\n");
    }
printk(KERN_INFO "for loop chl gya\n");
return 0;
}

//Deinitialization / removal of module

static void hello_exit(void)
{
printk(KERN_INFO "EXIT FROM THE DEVICE DRIVER\n");
}

//Module Registration

module_init(hello_init);
module_exit(hello_exit);

//Module information

MODULE_LICENSE("GPL");
MODULE_VERSION("V1.0");
MODULE_AUTHOR("LINUX");
MODULE_DESCRIPTION("FIRST PROG OF ELDD");
