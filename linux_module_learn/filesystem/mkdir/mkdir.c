#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>

static int __init mkdir_init(void)
{
	printk("mkdir_init\n");
	struct file *fp = (struct file *)NULL;
	fp = filp_open(
		"/run/media/black/Data/Documents/c/linux_module_learn/filesystem/mkdir/"
		"mkdir_test/",
		O_DIRECTORY | O_CREAT, S_IRUSR);
	if (IS_ERR(fp)) {
		printk("Error creating directory\n");
		return -1;
	}
	filp_close(fp, NULL);
	return 0;
}

static void __exit mkdir_exit(void)
{
	printk("mkdir_exit\n");
}

module_init(mkdir_init);
module_exit(mkdir_exit);
MODULE_LICENSE("GPL");
