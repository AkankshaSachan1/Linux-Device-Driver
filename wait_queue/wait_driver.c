#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/wait.h>

#define size 100
dev_t dev = 0; // (MKDEV(MAJOR,MINOR))
static struct cdev char_cdev ;
static struct class *dev_class ;
char flag='n';
char *k_buff;

//DECLARE_WAIT_QUEUE_HEAD(wq);
wait_queue_head_t wq;

//init_waitqueue_head(&wq);
static int __init mod_init(void);
static void __exit mod_exit(void);
static int device_open(struct inode *inode,struct file *fptr);
static int device_release(struct inode *inode,struct file *fptr);
static ssize_t device_write(struct file *fptr,const char *buffer,size_t count,loff_t *offp);
static ssize_t device_read(struct file *fptr,char *buffer,size_t count,loff_t *offp);

static const struct file_operations fops = 
{				
	.owner	 = THIS_MODULE,						
	.open	 = device_open,					
	.release = device_release,	
    .write   = device_write,
    .read    = device_read			
};
//user-space program requests to open the device file associated with the driver.
static int device_open(struct inode *inode,struct file *fptr)
{
    pr_info("initialize the device and allocate\n");
    return 0;
}


static ssize_t device_write(struct file *fptr,const char *buffer,size_t count,loff_t *offp)
{
    pr_info("write function invoked\n"); 
    
    copy_from_user(k_buff,buffer,count);
    pr_info("buff : %s\n",k_buff);
    flag = 'y';
    wake_up_interruptible(&wq);
    pr_info("wake\n");
    return count;
}

static ssize_t device_read(struct file *fptr,char *buffer,size_t count,loff_t *offp)
{
    pr_info("read function invoked\n");
    copy_to_user(buffer,k_buff,count);
    pr_info("buff : %s\n",k_buff);
    wait_event_interruptible(wq,flag=='y');
  // wait_event_timeout(wq,flag=='y',20000);
    flag='n';
    pr_info("wait\n");
    return count;
}
//user-space program closes the device file associated with the driver
static int device_release(struct inode *inode,struct file *fptr)
{
    pr_info("Deallocating the device\n");
    return 0;

}

static int __init mod_init(void)
{
    init_waitqueue_head(&wq);
  
    pr_info("Module loaded to kernel\n");

    //dynamic allocation of device numbers

    if((alloc_chrdev_region(&dev,0,1,"USER_DRIVER"))<0)
        {
            pr_info("cannot allocate major number\n");
            return -1;
        }

    printk("Major =%d  Minor =%d\n",MAJOR(dev),MINOR(dev));
    

//function used to initialize a struct cdev instance, which represents a character device in the Linux kernel.
    cdev_init(&char_cdev,&fops);

    if(cdev_add(&char_cdev,dev,1)<0)
    {
            pr_alert("cannot add device\n");
            return -1;
    }

    k_buff = kmalloc(size,GFP_KERNEL);
    if(k_buff==NULL){
        pr_alert("memory not allocated\n");
    }
    //dynamically creating device file
     if((dev_class = class_create(THIS_MODULE,"USER_MAIN_DRIVER"))==NULL)
     {
        pr_err("Cannot create class struct\n");
        goto r_class;
     }      
    if((device_create(dev_class,NULL,dev,NULL,"USER_MAIN_DRIVER"))==NULL)
    {
        pr_err("Can not create the device\n");
        goto r_device;
    }
    return 0;
    r_device:
        class_destroy(dev_class);
    r_class:
        unregister_chrdev_region(dev,1);
        return -1;
}
static void __exit mod_exit(void)
{
    device_destroy(dev_class,dev);
    class_destroy(dev_class);
     kfree(k_buff);
    cdev_del(&char_cdev);
    unregister_chrdev_region(dev,1);
    pr_info("Module removed from kernel\n");

}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("FILE OPEN AND RELEASE OPERATION");
