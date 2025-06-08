#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sysctl.h>

static int sysctl_kernusr_data = 1024;

static int kernusr_callback(struct ctl_table *table, int write,
			    void __user *buffer, size_t *lenp, loff_t *ppos)
{
	int rc;
	int *data = table->data;
	rc = proc_dointvec(table, write, buffer, lenp, ppos);

	printk(KERN_INFO "original value = %d\n", *data);

	if (write) {
		printk(KERN_INFO
		       "this is write operation, current value = %d\n",
		       *data);
	}

	return rc;
}

static struct ctl_table kernusr_ctl_table[] = {
	{
		// /proc/sys/ 下显示的文件名称
		.procname = "kernusr",
		.data = &sysctl_kernusr_data,
		.maxlen = sizeof(int),
		.mode = 0644,
		.proc_handler = kernusr_callback,
	},
	{
		/* sentinel */
	},
};

static struct ctl_table_header *sysctl_header;

static int __init sysctl_example_init(void)
{
	sysctl_header = register_sysctl_table(kernusr_ctl_table);
	if (sysctl_header == NULL) {
		printk(KERN_INFO "ERR: register_sysctl_table!");
		return -1;
	}

	printk(KERN_INFO "sysctl register success.\n");
	return 0;
}

static void __exit sysctl_example_exit(void)
{
	unregister_sysctl_table(sysctl_header);
	printk(KERN_INFO "sysctl unregister success.\n");
}

module_init(sysctl_example_init);
module_exit(sysctl_example_exit);
MODULE_LICENSE("GPL");
