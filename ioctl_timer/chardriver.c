#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/uaccess.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/ioctl.h>
#include<linux/timer.h>
#include<linux/jiffies.h>

#include"myioctl.h"

dev_t dev = 0;

static struct cdev char_cdev;
static struct timer_list mytimer;

int k_buff;
int led_count=0;

//function prototypes
static int __init dev_init(void);
static void __exit dev_exit(void);

static int char_open(struct inode *inode,struct file *fp);
static int char_release(struct inode *indoe,struct file *fp);

static ssize_t char_read(struct file *fp,char __user *buff,size_t len,loff_t *off);
static ssize_t char_write(struct file *fp,const char __user *buff,size_t len,loff_t *off);
static long char_ioctl(struct file *fp,unsigned cmd,unsigned long arg);
//file operation structure

static struct file_operations fops =
{
    .owner  = THIS_MODULE,
    .open   = char_open,
   .release = char_release,
      .read = char_read,
     .write = char_write,
.unlocked_ioctl = char_ioctl, 
};

static int char_open(struct inode *inode,struct file *fp)
{
    pr_info("Device is open..\n");
    return 0;
}

static int char_release(struct inode *inode,struct file *fp)
{
    pr_info("Device is closed\n");
    return 0;
}

static ssize_t char_write(struct file *fp,const char __user *buff,size_t len,loff_t *off)
{
    pr_info("Write fuunction invoked\n");
    return 0;
}

static ssize_t char_read(struct file *fp,char __user *buff,size_t len,loff_t *off)
{
    pr_info("Read function invoked\n");
    return 0;
}

static void timer_callback(struct timer_list *mytimer)
{
    if(led_count == 1){
        led_count = 0;
    }
    else
        led_count = 1;
    if(led_count==1)
    {
        pr_info("LED ON\n");
    }
    else
        pr_info("LED OFF\n");
        
   mod_timer(mytimer,jiffies+msecs_to_jiffies(k_buff));
}
//ioctl function

static long char_ioctl(struct file *fp,unsigned cmd,unsigned long arg)
{
    switch(cmd){
        case cmd_1 : led_count = 1;
            if(copy_from_user(&k_buff,(int8_t *)arg,sizeof(k_buff)))
            {
                return -EFAULT;
            }
        mod_timer(&mytimer,jiffies+msecs_to_jiffies(k_buff));
        pr_info("LED ON command recieve\n");
        break;

        // case 2: led_count = 0;
        //     if(copy_to_user((int8_t *)arg,&k_buff,sizeof(k_buff)))
        //     {
        //         return -EFAULT;
        //     }
        //  mod_timer(&mytimer,jiffies+msecs_to_jiffies(k_buff));
        // pr_info("LED OFF command recieve\n");
        // break;   
    }
    return 0;
}




static int __init dev_init(void)
{
        pr_info("MODULE INITIALIZE\n");

    if(alloc_chrdev_region(&dev,0,1,"ioctldriver")<0)
    {
        pr_err("Device no is not allocated\n");
        return -1;
    }
    pr_info("MAJOR=%d,MINOR=%d\n",MAJOR(dev),MINOR(dev));

    cdev_init(&char_cdev,&fops);

    if(cdev_add(&char_cdev,dev,1)<0)
    {
        pr_err("cannot add device\n");
        return -1;
    }

    timer_setup(&mytimer,timer_callback,led_count);
    return 0;
}

static void __exit dev_exit(void)
{
    del_timer(&mytimer);
    cdev_del(&char_cdev);
    unregister_chrdev_region(dev,1);
    pr_info("MODULE REMOVE\n");

}

module_init(dev_init);
module_exit(dev_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("IOCTL_TIMER");
