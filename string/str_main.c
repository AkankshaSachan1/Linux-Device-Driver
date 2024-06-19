#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include"header.h"

char *strptr = "linux device drivers";

char* str_rcv(void)
{
return strptr;
}

EXPORT_SYMBOL(str_rcv);

static int __init string_init(void)
{
printk(KERN_INFO "Module main.c initialized\n");
return 0;
}

static void __exit string_exit(void)
{
printk(KERN_INFO "Module removed!!\n");
}

module_init(string_init);
module_exit(string_exit);


MODULE_LICENSE("GPL");
MODULE_VERSION("V1.1");
MODULE_AUTHOR("USER");
