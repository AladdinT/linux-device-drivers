#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tohamy ");
MODULE_DESCRIPTION("A pseudo device drivers");

int major_num = 50;
module_param(major_num , int, 0664);
MODULE_PARM_DESC(major_num, "Represents the number of printing iterations");

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
    ret = register_chrdev(major_num, "pseudo_driver", &fops);
    if(ret >= 0)
    {
        printk("pseudo_driver was registered with major=%d , minor=%d  \n", major_num, 0);
    }
    else
    {
        printk("ERROR: could not register pseudo_driver with the specified major=%d \n", major_num);
        return ret;
    }
    return 0;
}

static void __exit pseudo_driver_bye(void)
{
    unregister_chrdev(major_num, "pseudo_driver");
    printk("Bye From Kernel \n");
}

module_init(pseudo_driver_hello);
module_exit(pseudo_driver_bye);

/*
    To list all devices' majors
    $ cat /proc/devices
    or 
    $ ls /dev -l 

    mknod - make block or character special files
    mknod [OPTION]... NAME TYPE [MAJOR MINOR]

    $ sudo mknod /dev/filename c 50 0
    $ cat /dev/filename
    $ sudo dmesg
    [  330.862067] pseudo_driver_open :: Pseudo Driver Opened
    [  330.862398] pseudo_driver_release :: Pseudo Driver Released
*/