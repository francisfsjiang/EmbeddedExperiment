#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/poll.h>
#include <linux/moduleparam.h>
#include <linux/wait.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

static int __init globalvar_init(void);
static void __exit globalvar_exit(void);
int globalvar_open(struct inode* inode, struct file* filp);
int globalvar_release(struct inode* inode, struct file* filp);
ssize_t globalvar_read(struct file *filp, char __user * buf, size_t len, loff_t *off);
ssize_t globalvar_write(struct file *filp, const char __user* buf, size_t len, loff_t *off);
long globalvar_ioctl(struct file *filp, unsigned int cmd, unsigned long args);
unsigned globalvar_poll(struct file *filp, struct poll_table_struct *poll_table);

struct file_operations globalvar_fops =
{
owner: THIS_MODULE,
       open: globalvar_open,
       release: globalvar_release,
       read: globalvar_read,
       write: globalvar_write,
       unlocked_ioctl: globalvar_ioctl,
       poll: globalvar_poll,
};

int dev_major = 50;
int dev_minor = 0;

struct globalvar_dev
{
	int read_able;
	int global_var;
	struct cdev cdev;
	wait_queue_head_t read_queue;
}*my_dev;


static int test_var = 0xFF;
module_param(test_var, int, 0644);


char DEVICE_NAME[16] = "globalvar_poll0";


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
	DEVICE_NAME[14] = 48 + DEVICE_NUM;

	printk("device name %s\n",DEVICE_NAME);

	ret = alloc_chrdev_region(&devno, dev_minor, 1, DEVICE_NAME);
	dev_major = MAJOR(devno);
	printk("device num %d\n",dev_major);

	if (ret < 0)
	{
		printk("register failed.\n");
		//globalvar_exit();
		return ret;
	}
	else
	{
		printk("%s\ngalbalvar init succeed.\n",DEVICE_NAME);
	}

	my_dev = kmalloc(sizeof(struct globalvar_dev), GFP_KERNEL);
	if (my_dev == NULL)
	{
		printk("kmalloc failed.\n");
	}
	else
	{
		printk("globalvar kmalloc succeed.\n");
		my_dev->read_able = 1;
		my_dev->global_var = test_var;
		//  Initializes cdev, remembering fops, making it ready to add to the system with cdev_add. 
		cdev_init(&my_dev->cdev, &globalvar_fops);
		my_dev->cdev.owner = THIS_MODULE;
		err = cdev_add(&my_dev->cdev, devno, 1);
		if (err < 0)
		{
			printk("add dev failed.\n");
		}
		printk("%s\nglobalvar cdev_add succeed.\n",DEVICE_NAME);
	}
	init_waitqueue_head(&my_dev->read_queue);
	printk("%s\ntest_var = 0x%x.\n", DEVICE_NAME,test_var);
	return ret;
}

static void __exit globalvar_exit(void)
{
	dev_t devno = MKDEV(dev_major, dev_minor);
	cdev_del(&my_dev->cdev);
	kfree(my_dev);
	unregister_chrdev_region(devno, 1);
	printk("%s\nglobalvar_exit called.\n", DEVICE_NAME);
	return ;
}

int globalvar_open(struct inode *inode, struct file *filp)
{
	struct globalvar_dev *dev;
	printk("%s\nglobalvar open called.\n",DEVICE_NAME);
	dev = container_of(inode->i_cdev, struct globalvar_dev, cdev);
	filp->private_data = dev;
	return 0;
}

int globalvar_release(struct inode *inode, struct file *filp)
{
	printk("%s\nglobalvar release called.\n", DEVICE_NAME);
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
	dev->read_able = 0;
	printk("%s\nglobalvar read called, global_var = 0x%x.\n",DEVICE_NAME,dev->global_var);
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
	dev->read_able = 1;
	//wake_up(&dev->read_queue);
	printk("%s\nglobalvar write called. global_var = 0x%x.\n", DEVICE_NAME,dev->global_var);
	return sizeof(int);
}

long globalvar_ioctl(struct file *filp, unsigned int cmd, unsigned long args)
{
	printk("%s\ncmd = 0x%x\n", DEVICE_NAME, cmd);
	return 0;
}

unsigned globalvar_poll(struct file *filp, struct poll_table_struct *poll_table)
{
	struct globalvar_dev *dev = filp->private_data;
	unsigned int mask = 0;

	poll_wait(filp, &dev->read_queue, poll_table);
	if (dev->read_able == 1)
	{
		mask |= POLLIN;
	}
	printk("%s\npoll mask 0x%x\n", DEVICE_NAME, mask);
	return mask;
}

module_init(globalvar_init);
module_exit(globalvar_exit);
