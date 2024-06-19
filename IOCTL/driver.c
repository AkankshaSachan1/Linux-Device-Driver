#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/uaccess.h>
#include<linux/slab.h>
#include<linux/kdev_t.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/ioctl.h>

#include"myioctl.h"


dev_t dev=0;

static struct cdev chardev;
static int k_buff;

static int __init mod_init(void);
static void __exit mod_exit(void);
static int chardev_open(struct inode *inode, struct file *file);
static int chardev_release(struct inode *inode,struct file *file);
static ssize_t chardev_read(struct file *file,char *buff,size_t count,loff_t *offp);
static ssize_t chardev_write(struct file *file,const char *buffer,size_t count,loff_t *offp);

static long chardev_ioctl(struct file *file,unsigned int cmd,unsigned long arg);



static const struct file_operations fops=
{
    .owner=THIS_MODULE,
    .open=chardev_open,
    .release=chardev_release,
    .write=chardev_write,
    .read=chardev_read,
    .unlocked_ioctl=chardev_ioctl,
};

static int chardev_open(struct inode *inode, struct file *file)
{
    pr_info("file opened\n");
    return 0;
}
static int chardev_release(struct inode *inode,struct file *file)
{
    pr_info("file closed\n");
    return 0;    
}
static ssize_t chardev_write(struct file *file,const char *buffer,size_t count,loff_t *offp)
{
    pr_info("write funtion invoked");
    return 0;
}
static ssize_t chardev_read(struct file *file,char *buff,size_t count,loff_t *offp)
{
    pr_info("read funtion invoked");
    return 0;
}
static long chardev_ioctl(struct file *file,unsigned int cmd,unsigned long arg)
{
    pr_info("ioctl1 function invoked");
    switch(cmd)
    {
        case cmd_1: if(copy_from_user(&k_buff,(int32_t *)arg,sizeof(k_buff)))
        		{
        			return  -EFAULT;
        		}
        		pr_info("VALUE SET IN DRIVER %d",k_buff);
                    break;  
        case cmd_2:
                    if(copy_to_user((int32_t *)arg,&k_buff,sizeof(k_buff)))
        		{
        			return  -EFAULT;
        		}
        		pr_info("VALUE from IN kernel %d",k_buff);
                        break;           
        case cmd_3: 
                     k_buff = 0;
                     pr_info("Value =%d\n",k_buff);
                    
                     break;

    }

    return 0;
}

static int __init mod_init(void){

    pr_info("mod initialize\n");

    if((alloc_chrdev_region(&dev,0,1,"ioctlfile"))<0)
        {
            pr_info("cannot allocate major number\n");
            return -1;
        }

    printk("Major =%d  Minor =%d\n",MAJOR(dev),MINOR(dev));


    cdev_init(&chardev,&fops);

    if(cdev_add(&chardev,dev,1)<0)
    {
            pr_alert("cannot add device\n");
            return -1;
    }

    return 0;
}
static void __exit mod_exit(void)
{
    cdev_del(&chardev);
    unregister_chrdev_region(dev,1);
    pr_info("Module removed from kernel\n");

}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ioctl OPERATION");
