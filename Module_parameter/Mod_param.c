#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

static char *ch;

module_param(ch,charp,S_IRUSR);

static int param_init(void)
{
printk("Device Driver initialized\n");
printk("Value of char = %s\n",ch);
return 0;
}

static void param_exit(void)
{
printk("Driver Removed\n");
}

module_init(param_init);
module_exit(param_exit);

MODULE_LICENSE("GPL");
MODULE_VERSION("V2.0");
MODULE_AUTHOR("MODULE");
MODULE_DESCRIPTION("MODULE PARAMETER PROG");
