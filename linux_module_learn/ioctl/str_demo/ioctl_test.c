#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/device.h>
#include "ioctl_test.h"

struct class *cls;
struct device *dev;
int major;
char kbuf[128] = { 0 };
int m_open(struct inode *inode, struct file *file)
{
	printk("%s:%s:%d\n", __FILE__, __func__, __LINE__);
	return 0;
}
ssize_t m_read(struct file *file, char __user *ubuf, size_t size, loff_t *loff)
{
	int ret;
	printk("%s:%s:%d\n", __FILE__, __func__, __LINE__);
	// 1.校验传输数据的大小，如果用户空间写的数据比内核空间数据大小大，需要更正大小
	if (size > sizeof(kbuf))
		size = sizeof(kbuf);
	// 2.将数据从用户空间拷贝到内核空间
	ret = copy_to_user(ubuf, kbuf, size);
	if (ret) // 3.判断是否错误
	{
		printk("copy to user is error\n");
		return -EIO;
	}
	return size; // 5.返回拷贝数据大小
}

long m_ioctl(struct file *file, unsigned int cmd, unsigned long args)
{
	int ret;
	char buf[128] = { 0 };
	image_t image;
	switch (cmd) {
	case UACCESS_BUF:
		ret = copy_from_user(buf, (void *)args, sizeof(buf));
		if (ret) {
			printk("copy from user is error\n");
			return -EIO;
		}
		printk("buf = %s\n", buf);
		break;
	case UACCESS_STRUCT:
		ret = copy_from_user(&image, (void *)args, sizeof(image_t));
		if (ret) {
			printk("copy from user is error\n");
			return -EIO;
		}
		printk("内核空间：width = %d  high = %d\n", image.width,
		       image.high);

		image.high += 10;
		image.width += 10;

		ret = copy_to_user((void *)args, &image, sizeof(image_t));
	default:
		printk("unknown cmd\n");
		break;
	}
	return 0;
}
ssize_t m_write(struct file *file, const char __user *ubuf, size_t size,
		loff_t *loff)
{
	int ret;
	printk("%s:%s:%d\n", __FILE__, __func__, __LINE__);
	// 1.校验传输数据的大小，如果用户空间写的数据比内核空间数据大小大，需要更正大小
	if (size > sizeof(kbuf))
		size = sizeof(kbuf);
	// 2.将数据从用户空间拷贝到内核空间
	ret = copy_from_user(kbuf, ubuf, size);
	if (ret) // 3.判断是否错误
	{
		printk("copy from user is error\n");
		return -EIO;
	}
	// 4.打印传递数据内容
	printk("copy from user kbuf:%s\n", kbuf);
	return size; // 5.返回拷贝数据大小
}
int m_close(struct inode *inode, struct file *file)
{
	printk("%s:%s:%d\n", __FILE__, __func__, __LINE__);
	return 0;
}

const struct file_operations fops = {
	.open = m_open,
	.read = m_read,
	.write = m_write,
	.unlocked_ioctl = m_ioctl,
	.release = m_close,
};
static int __init mycdev_init(void)
{
	// 1.注册字符设备驱动
	major = register_chrdev(0, CNAME, &fops);
	if (major < 0) // 2.判断返回值
	{
		printk("register chrdev is error\n");
	}
	// 3.打印主设备号
	printk("register chrdev major=%d\n", major);

	// 向上层提交目录信息
	cls = class_create(CNAME);
	if (IS_ERR(cls)) {
		printk("向上提交目录失败\n");
		PTR_ERR(cls);
	}
	printk("向上层提交目录信息成功\n");

	// 向上层提交设备信息
	dev = device_create(cls, NULL, MKDEV(major, 0), NULL, CNAME);
	if (IS_ERR(dev)) // 指针指向预留空间，函数调用失败
	{
		printk("向上提交设备失败\n");
		return PTR_ERR(dev);
	}

	printk("向上层提交设备信息成功\n");

	return 0;
}

static void __exit mycdev_exit(void)
{
	// 销毁向上层提交设备信息
	device_destroy(cls, MKDEV(major, 0));
	// 销毁向上层提交目录信息
	class_destroy(cls);

	// 1.注销字符设备驱动
	unregister_chrdev(major, CNAME);
}
module_init(mycdev_init);
module_exit(mycdev_exit);
MODULE_LICENSE("GPL");
