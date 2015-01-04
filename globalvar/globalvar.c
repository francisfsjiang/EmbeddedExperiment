#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

static int __init globalvar_init(void);
static void __exit globalvar_exit(void);
int globalvar_open(struct inode* inode, struct file* filp);
int globalvar_release(struct inode* inode, struct file* filp);
ssize_t globalvar_read(struct file *filp, char __user * buf, size_t len, loff_t *off);
ssize_t globalvar_write(struct file *filp, const char __user* buf, size_t len, loff_t *off);
long globalvar_ioctl(struct file *filp, unsigned int cmd, unsigned long args);

struct file_operations globalvar_fops =
        {
                owner: THIS_MODULE,
                open: globalvar_open,
                release: globalvar_release,
                read: globalvar_read,
                write: globalvar_write,
                unlocked_ioctl: globalvar_ioctl,
        };

int dev_major = 50;
int dev_minor = 0;

struct globalvar_dev
{
    int global_var;
    struct cdev cdev;
}*my_dev;


static int test_var = 0xFF;
module_param(test_var, int, 0644);

static int __init globalvar_init(void)
{
    int ret,err;
    dev_t devno = MKDEV(dev_major, dev_minor);

    /**
    * @dev output parameter for first assigned number 
    * @baseminor first of the requested range of minor numbers 
    * @count the number of minor numbers required 
    * @name the name of the associated device or driver 
    * int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unisgned count,const char *name);
    **/

    ret = alloc_chrdev_region(&devno, dev_minor, 1, "globalvar");
    dev_major = MAJOR(devno);
    printk("dev majon num: %d\n",dev_major);

    if (ret < 0)
    {
        printk("register failed.\n");
        //globalvar_exit();
        return ret;
    }
    else
    {
        printk("galbalvar init succeed.\n");
    }

    my_dev = kmalloc(sizeof(struct globalvar_dev), GFP_KERNEL);
    if (my_dev == NULL)
    {
        printk("kmalloc failed.\n");
    }
    else
    {
        printk("globalvar kmalloc succeed.\n");
        my_dev->global_var = test_var;
	//  Initializes cdev, remembering fops, making it ready to add to the system with cdev_add. 
        cdev_init(&my_dev->cdev, &globalvar_fops);
        my_dev->cdev.owner = THIS_MODULE;
        err = cdev_add(&my_dev->cdev, devno, 1);
        if (err < 0)
        {
            printk("add dev failed.\n");
        }
        printk("globalvar cdev_add succeed.\n");
    }
    printk("test_var = 0x%x.\n", test_var);
    return ret;
}

static void __exit globalvar_exit(void)
{
    dev_t devno = MKDEV(dev_major, dev_minor);
    cdev_del(&my_dev->cdev);
    kfree(my_dev);
    unregister_chrdev_region(devno, 1);
    printk("globalvar_exit called.\n");
    return ;
}

int globalvar_open(struct inode *inode, struct file *filp)
{
    struct globalvar_dev *dev;
    printk("globalvar open called.\n");
    dev = container_of(inode->i_cdev, struct globalvar_dev, cdev);
    filp->private_data = dev;
    return 0;
}

int globalvar_release(struct inode *inode, struct file *filp)
{
    printk("globalvar release called.\n");
    return 0;
}

ssize_t globalvar_read(struct file *filp, char __user* buf, size_t len, loff_t *off)
{
    struct globalvar_dev *dev = filp->private_data;
    int ret;
    ret = copy_to_user((void*)buf, (const void*)&dev->global_var, sizeof(int));
    if (ret < 0)
    {
        return -EFAULT;
    }
    printk("globalvar read called, global_var = 0x%x.\n",dev->global_var);
    return sizeof(int);
}

ssize_t globalvar_write(struct file *filp, const char __user* buf, size_t len, loff_t *off)
{
    struct globalvar_dev *dev = filp->private_data;
    int ret;
    ret = copy_from_user((void*)&dev->global_var, (const void*)buf, sizeof(int));
    if (ret < 0)
    {
        return -EFAULT;
    }
    printk("globalvar write called. \n");
    return sizeof(int);
}

long globalvar_ioctl(struct file *filp, unsigned int cmd, unsigned long args)
{
    printk("cmd = 0x%x\n", cmd);
    return 0;
}

module_init(globalvar_init);
module_exit(globalvar_exit);
