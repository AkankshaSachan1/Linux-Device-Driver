#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/kdev_t.h>
#include<linux/device.h>
#include<linux/uaccess.h>
#include<linux/ioctl.h>
#include "myioctl.h"

static char k_buff[100];

dev_t dev=0;
static struct cdev char_dev;
static struct class *dev_class;

static int __init mod_init(void);
static void __exit mod_exit(void);
static int char_open(struct inode *inode,struct file *file);
static int char_release(struct inode *inode,struct file *file);
static ssize_t char_read(struct file *file,char __user *buffer,size_t len,loff_t *offp);
static ssize_t char_write(struct file *file,const char __user *buffer,size_t len,loff_t *offp);
static long char_ioctl(struct file *file,unsigned int cmd,unsigned long arg);

static struct file_operations fops=
{
    .owner=THIS_MODULE,
    .open=char_open,
    .release=char_release,
    .read=char_read,
    .write=char_write,
    .unlocked_ioctl=char_ioctl,
};

static int char_open(struct inode *inode,struct file *file)
{
    pr_info("Open function invoked\n");
    return 0;
}
static int char_release(struct inode *inode,struct file *file)
{
    pr_info("Release function invoked\n");
    return 0;
}
static ssize_t char_read(struct file *file,char __user *buffer,size_t len,loff_t *offp)
{
    if(copy_to_user(buffer,k_buff,len))
    {
        return -EFAULT;
    }
    device_stats.rw=0;
    pr_info("Read %ld bytes from device\n",len);
    return len;
}
static ssize_t char_write(struct file *file,const char __user *buffer,size_t len,loff_t *offp)
{
    if(copy_from_user(k_buff,buffer,len))
    {
        return -EFAULT;
    }
    device_stats.size=len;
    strncpy(device_stats.buffer,k_buff,len);
    pr_info("Wrote %ld bytes to device\n",len);
    return len;
}
static long char_ioctl(struct file *file,unsigned int cmd,unsigned long arg)
{
    switch(cmd)
    {
        case cmd_1:
            if(copy_to_user((struct stats *)arg,&device_stats,sizeof(device_stats)))
            {
                return -EFAULT;
            }
            break;
        default:
            return -EINVAL;
    }
    return 0;
}

static int __init mod_init(void)
{
    pr_info("MODULE INTIALISED\n");

    if(alloc_chrdev_region(&dev,0,3,"Character driver")<0)
    {
        pr_err("Device number is not allocated\n");
        return -1;
    }
    pr_info("MAJOR=%d\tMINOR=%d\n",MAJOR(dev),MINOR(dev));

   cdev_init(&char_dev,&fops);

   if(cdev_add(&char_dev,dev,3)<0)
   {
    pr_err("Device not added\n");
    return -1;
   } 
    dev_class=class_create(THIS_MODULE,"driver");
    int i;
    for(i=0;i<3;i++)
    {
        device_create(dev_class,NULL,MKDEV(MAJOR(dev),i),NULL,"driver%d",i);
    }
    return 0;
}

static void __exit mod_exit(void)
{
    int i;
    for(i=0;i<3;i++)
    {
        device_destroy(dev_class,MKDEV(MAJOR(dev),i));
    }
    class_destroy(dev_class);
    cdev_del(&char_dev);
    unregister_chrdev_region(dev,3);
    pr_info("MODULE REMOVED\n");
}
module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("FILE OPEN AND RELEASE OPERATION");
