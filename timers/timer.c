#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/timer.h>
#include<linux/jiffies.h>

static struct timer_list mytimer;
static struct timer_list nexttimer;
int count =0;

void next_callback_func(struct timer_list *nexttimer)
{  
    while(count<10){
        pr_info("PRINT in between EXECUTION %d\n",count);
         count++;
    }
    mod_timer(&mytimer,jiffies+msecs_to_jiffies(20000));
}
void callback_func(struct timer_list *mytimer)
{  
    
        pr_info("PRINT AFTER EXECUTION %d\n",count);
    
    
}

static int __init timer_init(void)
{
    pr_info("MODULE INITIALISATION\n");
    
     timer_setup(&nexttimer,next_callback_func,count);
     add_timer(&nexttimer);
     mod_timer(&nexttimer,jiffies+msecs_to_jiffies(5000));
     
     timer_setup(&mytimer,callback_func,count);
    
    return 0;
}

static void __exit timer_exit(void)
{
    pr_info("MODULE ENDED\n");
    del_timer(&mytimer);
    del_timer(&nexttimer);

}
//Module Registration

module_init(timer_init);
module_exit(timer_exit);

//Module Info
MODULE_LICENSE("GPL");
MODULE_VERSION("V2.3");
MODULE_AUTHOR("USER");
MODULE_DESCRIPTION("timer func implementation");