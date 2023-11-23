#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tohamy ");
MODULE_DESCRIPTION("A pseudo device drivers with dynamic device number");

dev_t device_number;
static int __init pseudo_driver_hello(void)
{
    int ret;
    // alloc_chrdev_region — register a range of char device numbers
    ret = alloc_chrdev_region(&device_number, 0, 1, "pseudo_driver");
    
    if(ret >= 0)
    {
        printk("pseudo_driver was registered with major=%d , minor=%d  \n", MAJOR(device_number), MINOR(device_number));
    }
    else
    {
        printk("ERROR: could not register pseudo_driver with the specified major=%d \n", MAJOR(device_number));
        return ret;
    }
    return 0;
}

static void __exit pseudo_driver_bye(void)
{
    // unregister_chrdev_region — unregister a range of device numbers
    unregister_chrdev_region (device_number , 1);
    printk("Bye From Kernel \n");
}

module_init(pseudo_driver_hello);
module_exit(pseudo_driver_bye);
