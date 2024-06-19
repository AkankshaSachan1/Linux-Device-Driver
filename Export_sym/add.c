#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include"header.h"

int a = 15;
int b = 2;

static int __init add_init(void)
{
printk("sum is %d\n",sum(a,b));
return 0;
}

static void __exit add_exit(void)
{
printk("Calculation completed!!\n");
}

module_init(add_init);
module_exit(add_exit);

MODULE_LICENSE("GPL");
MODULE_VERSION("V2.1");
MODULE_AUTHOR("USER");


