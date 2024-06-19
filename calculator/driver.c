#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/device.h>
#include<linux/slab.h>
#include<linux/semaphore.h>

dev_t dev=0;
static struct cdev char_cdev;
static struct class *devclass;
int res;

static int __init dev_init(void);
static void __exit dev_exit(void);

static int char_open(struct inode *inode,struct file *file);
static int char_release(struct inode *inode,struct file *file);
static ssize_t char_read(struct file *file,char __user *buffer,size_t len,loff_t *offp);
static ssize_t char_write(struct file *file,const char __user *buffer,size_t len,loff_t *offp);

//file operation structure

static const struct file_operations fops=
{
    .owner=THIS_MODULE,
    .open=char_open,
    .release=char_release,
    .read=char_read,
    .write=char_write,
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
static ssize_t char_write(struct file *file,const char __user *buffer,size_t len,loff_t *offp)
{
    int k_buff[2];
    pr_info("Write function invoked\n");
    if(copy_from_user(k_buff,buffer,sizeof(k_buff)))
    {
        pr_err("data write error\n");
        return -EFAULT;
    }
    int num1=k_buff[0];
    int num2=k_buff[1];
    pr_info("num1=%d\tnum2=%d\n",num1,num2);
    switch(MINOR(file->f_inode->i_rdev))
    {
        case 0: //add
            pr_info("MAJOR=%d,MINOR=%d",MAJOR(dev),MINOR(file->f_inode->i_rdev));
            res=num1+num2;
            pr_info("%d=%d+%d\n",res,num1,num2);
            break;
        case 1: //sub
            pr_info("MAJOR=%d,MINOR=%d",MAJOR(dev),MINOR(file->f_inode->i_rdev));
            res=num1-num2;
            pr_info("%d=%d-%d\n",res,num1,num2);
            break;
        case 2: //mul
            pr_info("MAJOR=%d,MINOR=%d",MAJOR(dev),MINOR(file->f_inode->i_rdev));
            res=num1*num2;
            pr_info("%d=%d*%d",res,num1,num2);
            break;
        case 3: //div
            pr_info("MAJOR=%d,MINOR=%d",MAJOR(dev),MINOR(file->f_inode->i_rdev));
            if(num1>num2)
            {
                res=num1/num2;
                pr_info("%d=%d/%d\n",res,num1,num2);
            }
            else{
                pr_info("wrong input\n");
                return -1;
            }
            break;
        default:
            return -EINVAL;    
    }
    pr_info("Write function completed\n");
    return len;
}
static ssize_t char_read(struct file *file,char __user *buffer,size_t len,loff_t *offp)
{
    pr_info("Read function completed\n");
    if(copy_to_user(buffer,&res,len))
    {
        pr_err("data reading error\n");
        return -EFAULT;
    }
    pr_info("res=%d\n",res);
    pr_info("read function completed\n");
    return len;
}

static int __init dev_init(void)
{
    pr_info("Module initialised\n");

    if(alloc_chrdev_region(&dev,0,5,"char_driver")<0)
    {
        pr_info("device no not allocated");
        return -1;
    }
    pr_info("MAJOR=%d\tMINOR=%d\n",MAJOR(dev),MINOR(dev));

    cdev_init(&char_cdev,&fops);

    if(cdev_add(&char_cdev,dev,5)<0)
    {
        pr_info("Device not added\n");
        return -1;
    }
    devclass=class_create(THIS_MODULE,"calculatordevice");
    int i=0;
    for(i=0;i<5;i++)
    {
        device_create(devclass,NULL,MKDEV(MAJOR(dev),i),NULL,"Calculator%d",i);
    }
    return 0;
}

static void __exit dev_exit(void)
{
    int i;
    for(i=0;i<5;i++)
    {
        device_destroy(devclass,MKDEV(MAJOR(dev),i));
    }
    class_destroy(devclass);
    cdev_del(&char_cdev);
    unregister_chrdev_region(dev,5);
    pr_info("MODULE REMOVED\n");
}
module_init(dev_init);
module_exit(dev_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("FILE OPEN AND RELEASE OPERATION");