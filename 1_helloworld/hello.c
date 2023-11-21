#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

static int __init driver_hello(void)
{
    printk("Hello From Kernel \n");

    return 0;
}

static void __exit driver_bye(void)
{
    printk("Bye From Kernel \n");
}

module_init(driver_hello);
module_exit(driver_bye);

// lsmod
// insmod
// rmmod
