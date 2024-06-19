#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include"header.h"


int sum(int a,int b)
{
return (a+b);
}


EXPORT_SYMBOL(sum);

static int __init cal_init(void)
{
printk("Module Initialize for calculation\n");
return 0;
}

static void __exit cal_exit(void)
{
printk("module removed after calculation\n");
}

module_init(cal_init);
module_exit(cal_exit);


MODULE_LICENSE("GPL");
MODULE_VERSION("V1.1");
MODULE_AUTHOR("USER");
