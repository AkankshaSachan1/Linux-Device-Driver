#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/wait.h>
#include<linux/semaphore.h>
#include<linux/device.h>

dev_t dev=0;
static struct cdev char_cdev;
static struct class *dev_class;
static struct semaphore my_sema;
wait_queue_head_t wq;
//DECLARE_WAIT_QUEUE_HEAD(wq);
static int flag=0;
char k_buff[50];

static int __init mod_init(void);
static void __exit mod_exit(void);
static int char_open(struct inode *inode,struct file *file);
static int char_release(struct inode *inode,struct file *file);
static ssize_t char_read(struct file *file,char __user *buffer,size_t len,loff_t *offp);
static ssize_t char_write(struct file *file,const char __user *buffer,size_t len,loff_t *offp);

static struct file_operations fops =
{
    .owner=THIS_MODULE,
    .open=char_open,
    .release=char_release,
    .read=char_read,
    .write=char_write,
};

static int char_open(struct inode *inode,struct file *file)
{
    pr_info("device opened\n");
    return 0;
}

static int char_release(struct inode *inode,struct file *file)
{
    pr_info("device closed\n");
    return 0;
}

static ssize_t char_read(struct file *file,char __user *buffer,size_t len,loff_t *offp)
{
    if((copy_to_user((char *)buffer,(char *)k_buff,sizeof(k_buff)))==0)
    {
        pr_info("Data read successfully\n");
    }
    else
    {
        pr_info("Error in data reading\n");
    }
    up(&my_sema);
    flag=1;
    wake_up_interruptible(&wq);
    return 0;
}
static ssize_t char_write(struct file *file,const char __user *buffer,size_t len,loff_t *offp)
{
    
    down_interruptible(&my_sema);
    if(copy_from_user((char *)k_buff,(char *)buffer,sizeof(k_buff))==0)
    {
        pr_info("Data return successfully\n");
        pr_info("Data Received=%s\n",k_buff);
    }
    else
    {
        pr_info("Error in writing\n");
    }
    wait_event_interruptible(wq,flag!=0);
    pr_info("Process went to sleep\n");
    if(flag!=0)
    {
        pr_info("Wake up successfull\n");
    }
    flag=0;
    return len;
}

static int __init mod_init(void)
{
     pr_info("Module initialised\n");
    if(alloc_chrdev_region(&dev,0,2,"chardriver")<0)
    {
        pr_info("device no not allocated");
        return -1;
    }
    pr_info("MAJOR=%d\tMINOR=%d\n",MAJOR(dev),MINOR(dev));

    cdev_init(&char_cdev,&fops);
    if(cdev_add(&char_cdev,dev,2)<0)
    {
        pr_info("Device not added\n");
        return -1;
    }
    dev_class=class_create(THIS_MODULE,"char_driver");
    int i=0;
    for(i=0;i<2;i++)
    {
        device_create(dev_class,NULL,MKDEV(MAJOR(dev),i),NULL,"operation%d",i);
    }
    sema_init(&my_sema,1);
    init_waitqueue_head(&wq);
    return 0;
}

static void __exit mod_exit(void)
{
    int i=0;
    for(i=0;i<2;i++)
    {
        device_destroy(dev_class,MKDEV(MAJOR(dev),i));
    }
    class_destroy(dev_class);
    cdev_del(&char_cdev);
    unregister_chrdev_region(dev,2);
    pr_info("MODULE REMOVED\n");
}
module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("FILE OPEN AND RELEASE OPERATION");