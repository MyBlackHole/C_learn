#include <linux/dcache.h>
#include <linux/debugfs.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/uaccess.h>

static char zen_buf[512] = "hello\n";
static struct dentry *zen_dir;

static int zen_open(struct inode *inode, struct file *filp)
{
	printk("zen open\n");
	filp->private_data = inode->i_private;
	return 0;
}

ssize_t zen_read(struct file *filp, char __user *buf, size_t count,
		 loff_t *offp)
{
	int retval = 0;
	if ((*offp + count) > 512) {
		count = 512 - *offp;
	}

	printk("read request: count:%ld, offset:%lld\n", count, *offp);
	if (copy_to_user(buf, zen_buf + *offp, count)) {
		printk("copy to user failed, count:%ld\n", count);
		retval = -EFAULT;
		goto out;
	}
	*offp += count;
	retval = count;
out:
	return retval;
}

ssize_t zen_write(struct file *filp, const char __user *buff, size_t count,
		  loff_t *offp)
{
	int retval;
	printk("write request: count:%ld, offset:%lld\n", count, *offp);
	if (*offp > 512) {
		return 0;
	}

	if (*offp + count > 512) {
		count = 512 - *offp;
	}

	if (copy_from_user(zen_buf + *offp, buff, count)) {
		printk("copy from user failed, count:%ld\n", count);
		retval = -EFAULT;
		goto out;
	}
	*offp += count;
	retval = count;
out:
	return retval;
}

struct file_operations my_fops = {
	.owner = THIS_MODULE,
	.read = zen_read,
	.write = zen_write,
	.open = zen_open,
};

static int __init debugfs_init(void)
{
	static struct dentry *sub_zen_dir;
	struct dentry *filent;
	printk("INIT MODULE\n");
	zen_dir = debugfs_create_dir("zen_dir4", NULL);
	if (!zen_dir) {
		printk("zen_dir4 is null\n");
		goto fail;
	}
	sub_zen_dir = debugfs_create_dir("sub_zen", zen_dir);
	if (!sub_zen_dir) {
		printk("sub zen dir is null\n");
		goto fail;
	}
	// 0644
	filent = debugfs_create_file("zen",
				     S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH,
				     sub_zen_dir, NULL, &my_fops);
	if (!filent) {
		printk("zen file is null\n");
		goto fail;
	}
	printk("INIT SUCCESS\n");
	return 0;
fail:
	// return -ENOENT;
	return -1;
}

static void __exit debugfs_exit(void)
{
	printk("exit module\n");
	debugfs_remove_recursive(zen_dir);
	printk("exit success\n");
}

module_init(debugfs_init);
module_exit(debugfs_exit);
MODULE_LICENSE("GPL");
