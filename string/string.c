#include<stdio.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include"header.h"

static int __init string1_init(void)
{
    char *ptr =  str_rcv();
printk(KERN_INFO "string.c initialized\n");
printk(KERN_INFO "string is %s\n",ptr);
return 0;
}

static void __exit string1_exit(void)
{
printk(KERN_INFO "string received \t string.c removed\n");
}

module_init(string1_init);
module_exit(string1_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("USER");
MODULE_DESCRIPTION("STRING PASS FROM EXPORT_SYMBOL");
