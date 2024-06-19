#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/kdev_t.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/spinlock.h>
#include<linux/types.h>
#include<linux/slab.h>
#include<linux/spinlock.h>
# define size 100

dev_t dev=0;
spinlock_t my_spin;
unsigned int op_result;
static struct cdev char_cdev;

static int __init mod_init(void);
static void __exit mod_exit(void);
static int device_open(struct inode *inode,struct file *filep);
static int device_release(struct inode *inode,struct file *filep);
static ssize_t device_read(struct file *fptr,char *buffer,size_t count,loff_t *offp);
static ssize_t device_write(struct file *fptr,const char *buffer,size_t count,loff_t *offp);

static const struct file_operations fops =
{
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
    .write = device_write,
    .read = device_read,
};
// static const struct file_operations fops = 
// {				
// 	.owner	 = THIS_MODULE,						
// 	.open	 = device_open,					
// 	.release = device_release,	
//     .write   = device_write,
//     .read    = device_read,				
// };
static int device_open(struct inode *inode,struct file *filep)
{
    pr_info("Open Function\n");
    return 0;
}
static int device_release(struct inode *inode,struct file *filep)
{
    pr_info("Close Function\n");
    return 0;
}
static ssize_t device_write(struct file *fptr,const char *buffer,size_t count,loff_t *offp)
{
    spin_lock(&my_spin);
    pr_info("Write Function\n");
    int k_buff[2];
    int result,num1,num2;
    result=copy_from_user((char *)k_buff,(char *)buffer,sizeof(k_buff));
    if(result==0)
    {
        pr_info("Successfully written inkernel\n");
        num1=k_buff[0];
        num2=k_buff[1];
        op_result=num1+num2;
        pr_info("Result in write section driver %d\n",op_result);
        return count;
    }
    else{
        pr_err("Error in writing from user to kernel\n");
        return -1;
    }
}

static ssize_t device_read(struct file *fptr,char *buffer,size_t count,loff_t *offp)
{
    pr_info("Read Function\n");
    int result = copy_to_user((char *)buffer,&op_result,sizeof(op_result));
    if(result==0)
    {
        pr_info("Data read successfully from kernel to user\n");
        pr_info("Result in read section %d\n",op_result);
        spin_unlock(&my_spin);
        return count;
    }
    else
    {
        pr_err("error in reading data from kernel to user\n");
        return -3;
    }
}

static int __init mod_init(void)
{
    pr_info("Module Initialise\n");

    if((alloc_chrdev_region(&dev,0,3,"Spin_driver"))<0)
    {
        pr_err("Cannot allocate major number\n");
        return -1;
    }
    pr_info("MAJOR =%d\tMINOR=%d\n",MAJOR(dev),MINOR(dev));

    cdev_init(&char_cdev,&fops);
    if(cdev_add(&char_cdev,dev,3)<0)
    {
        pr_err("Cannot add the device\n");
        return -2;
    }
    // k_buff=kmalloc(size,GFP_KERNEL);
    // if(k_buff==NULL)
    // {
    //     pr_err("Memory not allocated\n");
    // }
    spin_lock_init(&my_spin);
     return 0;
}
static void __exit mod_exit()
{
   // kfree(k_buff);
    cdev_del(&char_cdev);
    unregister_chrdev_region(dev,1);
    pr_info("MODULE REMOVED SUCCESSFULLY\n");
}
module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
MODULE_VERSION("1.1");
MODULE_DESCRIPTION("spin lock driver");

