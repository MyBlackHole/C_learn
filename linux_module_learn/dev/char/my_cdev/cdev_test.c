#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "cdev_test"
#define CLASS_NAME "my_cdev"
#define TRUE 1
#define FALSE 0

static int majorNumber;
static struct class *decdevClass = NULL;
static struct device *decdev = NULL;

char *Message;
int isKeyRead = FALSE;
int Length;

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = {
	.open = dev_open,
	.read = dev_read,
	.write = dev_write,
	.release = dev_release,
};

static int __init decdev_init(void)
{
	// 0 代表动态分配 majorNumber
	majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
	Message = kmalloc(200, GFP_KERNEL);
	Length = 0;
	if (majorNumber < 0) {
		return majorNumber;
	}
	// 创建设备类 (创建设备文件时需要指定设备类, 用于自动创建设备节点)
	decdevClass = class_create(CLASS_NAME);
	if (IS_ERR(decdevClass)) {
		unregister_chrdev(majorNumber, DEVICE_NAME);
		return PTR_ERR(decdevClass);
	}
	// 在 dev 目录下创建 decdevClass 的 majorNumber 节点
	decdev = device_create(decdevClass, NULL, MKDEV(majorNumber, 0), NULL,
			       DEVICE_NAME);
	if (IS_ERR(decdev)) {
		class_destroy(decdevClass);
		unregister_chrdev(majorNumber, DEVICE_NAME);
		return PTR_ERR(decdev);
	}
	printk(KERN_ALERT "%s: Module initialized", DEVICE_NAME);
	return 0;
}

static void __exit decdev_exit(void)
{
	kfree(Message);
	device_destroy(decdevClass, MKDEV(majorNumber, 0));
	class_unregister(decdevClass);
	class_destroy(decdevClass);
	unregister_chrdev(majorNumber, DEVICE_NAME);
}

static int dev_open(struct inode *inodep, struct file *filep)
{
	printk("%s: open", DEVICE_NAME);
	return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len,
			loff_t *offset)
{
	int ret;
	int ret_len;

	printk("%s: dev_read Length:[%d], len:[%ld]", DEVICE_NAME, Length, len);

	// 内核空间到用户空间 Message --> buffer
	ret = copy_to_user(buffer, Message, Length);

	if (ret != 0) {
		return -EFAULT;
	}
	ret_len = Length;
	Length = 0;
	return ret_len;
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len,
			 loff_t *offset)
{
	int ret;
	// 用户空间到内核空间 buffer --> Message
	ret = copy_from_user(Message, buffer, len);
	if (ret != 0) {
		return -EFAULT;
	}
	Message[len] = '\0';
	Length = len;
	Length++;
	printk("%s: dev_write Length:[%d], len:[%ld]", DEVICE_NAME, Length,
	       len);
	return len;
}

static int dev_release(struct inode *inodep, struct file *filep)
{
	// Length = 0;
	printk("%s: dev_release", DEVICE_NAME);
	return 0;
}

module_init(decdev_init);
module_exit(decdev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lakshya A Agrawal");
MODULE_DESCRIPTION("A simple device driver for XOR decryption");
