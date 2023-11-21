#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tohamy ");
MODULE_DESCRIPTION("A Psuedo device driver with parameter");

int count = 0 ;

module_param(count, int, 664);

static int __init driver_hello(void)
{
    int i = 0 ; // Standard Requirement
    for(i=0; i<count ; i++)
    {
        printk("Hello From Kernel \n");
    }

    return 0;
}

static void __exit driver_bye(void)
{
    int i = 0 ; // Standard Requirement
    for(i=0; i<count ; i++)
    {
        printk("Bye From Kernel \n");
    }
}

module_init(driver_hello);
module_exit(driver_bye);
