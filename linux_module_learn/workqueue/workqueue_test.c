#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/power_supply.h>
#include <linux/kobject.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/time64.h>
#include <linux/of.h>
#include <linux/completion.h>
#include <linux/mfd/core.h>
#include <linux/kernel.h>
#include <linux/seq_file.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>

struct work_struct work_demo;
struct work_struct work_demo2;

struct workqueue_struct *workqueue_demo;

static void work_demo_func(struct work_struct *work)
{
	printk("%s ,cpu id = %d,taskname = %s\n", __func__,
	       raw_smp_processor_id(), current->comm);
	mdelay(1000 * 10);
}

static int workqueue_proc_show(struct seq_file *seq_file, void *data)
{
	printk("%s ,cpu id = %d\n", __func__, raw_smp_processor_id());

	schedule_work(&work_demo);

	return 0;
}

static int workqueue_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, workqueue_proc_show, NULL);
}

static ssize_t workqueue_proc_store(struct file *file,
				    const char __user *buffer, size_t count,
				    loff_t *ppos)
{
	int ret;
	char *buf;
	buf = kmalloc(count, GFP_KERNEL);
	if (!buf) {
		return -1;
	}

	ret = copy_from_user(buf, buffer, count);
	if (ret < 0) {
		return ret;
	}

	if (buf[0] == '1') {
		printk("%s ,work_demo,cpu id = %d\n", __func__,
		       raw_smp_processor_id());
		queue_work(workqueue_demo, &work_demo);
		printk("queue work_demo end\n");
	} else if (buf[0] == '2') {
		printk("%s ,work_demo2,cpu id = %d\n", __func__,
		       raw_smp_processor_id());
		queue_work(workqueue_demo, &work_demo2);
	}
	kfree(buf);

	return count;
}

static const struct proc_ops workqueue_proc_fops = {
	.proc_open = workqueue_proc_open,
	.proc_read = seq_read,
	.proc_write = workqueue_proc_store,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};

static int __init workqueue_test_init(void)
{
	INIT_WORK(&work_demo, work_demo_func);
	INIT_WORK(&work_demo2, work_demo_func);
	workqueue_demo = alloc_workqueue("workqueue_demo", 0, 2);

	proc_create("workqueue", 0, NULL, &workqueue_proc_fops);

	return 0;
}

static void __exit workqueue_exit(void)
{
	return;
}

MODULE_LICENSE("GPL");
module_init(workqueue_test_init);
module_exit(workqueue_exit);
