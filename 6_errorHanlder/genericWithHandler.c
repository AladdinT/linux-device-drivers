#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tohamy ");
MODULE_DESCRIPTION("A pseudo device drivers with dynamic device number");

dev_t device_number;
struct cdev my_cdev;
struct class* my_class;
struct device * my_device;

int pseudo_driver_open (struct inode *, struct file *)
{
    printk("%s :: Pseudo Driver Opened\n" , __FUNCTION__);
    return 0;
}

int pseudo_driver_release (struct inode *, struct file *)
{
    printk("%s :: Pseudo Driver Released\n" , __FUNCTION__);
    return 0;
}

struct file_operations fops = 
{
    .owner = THIS_MODULE,
    .open = pseudo_driver_open,
    .release = pseudo_driver_release
};



static int __init pseudo_driver_hello(void)
{
    int ret;
    // ## 1 ## Allocate dynamic device number
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

    // ## 2 ## Create a character device
    cdev_init(&my_cdev, &fops);
    ret = cdev_add(&my_cdev, device_number, 1);
    // if addition failed
    if(ret != 0)
    {
        printk("%s : cdev addition failed\n", __FUNCTION__);
        goto CDEV_ERR;
    }
    
    // ## 3 ## Genereate /dev file 
    // class_create - create a struct class structure
    my_class = class_create(THIS_MODULE, "my_class");
    // if class creation failed
    if(my_class == NULL)
    {
        printk("%s : class creation failed\n", __FUNCTION__);
        goto CLASS_ERR;
    }
    
    // device_create - creates a device and registers it with sysfs
    my_device=device_create(my_class, NULL, device_number, NULL, "my_file");

    // if device creation failed
    if(my_device == NULL)
    {
        printk("%s : device creation failed\n", __FUNCTION__);
        goto DEV_ERR;
    }
    return 0;

    DEV_ERR:
        class_destroy(my_class);        
    CLASS_ERR:
        cdev_del(&my_cdev);
    CDEV_ERR:
        unregister_chrdev_region (device_number , 1);        
    return -1;
}

static void __exit pseudo_driver_bye(void)
{
    // Destroy Device (mind PRIORITY)
    device_destroy(my_class, device_number);
    // Destroy class
    class_destroy(my_class);
    // Delete created cdev
    cdev_del(&my_cdev);
    // free registered device number  (mind PRIORITY)
    unregister_chrdev_region (device_number , 1);

    printk("Bye From Kernel \n");
}

module_init(pseudo_driver_hello);
module_exit(pseudo_driver_bye);
