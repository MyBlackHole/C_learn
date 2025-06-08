#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/wait.h>
#include <linux/kthread.h>

static atomic_t read_count = ATOMIC_INIT(0);
static struct task_struct *wait_thread;
// Initializing waitqueue statically
DECLARE_WAIT_QUEUE_HEAD(test_wait_queue);
static atomic_t wait_queue_flag = ATOMIC_INIT(0);

static int my_waitqueue_show(struct seq_file *m, void *v)
{
	printk(KERN_INFO "Read function\n");
	seq_printf(m, "read_count = %d\n", atomic_read(&read_count));
	atomic_set(&wait_queue_flag, 1);

	// wake up only one process from wait queue
	wake_up_interruptible(&test_wait_queue);
	return 0;
}

static int my_waitqueue_open(struct inode *inode, struct file *filp)
{
	return single_open(filp, my_waitqueue_show, NULL);
}

static struct file_operations test_wait_queue_fops = {
	.open = my_waitqueue_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int wait_function(void *unused)
{
	while (!kthread_should_stop()) {
		printk(KERN_INFO "Waiting For Event...\n");
		// sleep until wait_queue_flag != 0
		if (wait_event_interruptible(test_wait_queue,
					     atomic_read(&wait_queue_flag) !=
							     0 ||
						     kthread_should_stop())) {
			if (kthread_should_stop())
				break;
			continue;
		}
		if (atomic_read(&wait_queue_flag) == 2) {
			printk(KERN_INFO "Event Came From Exit Function\n");
			return 0;
		}
		printk(KERN_INFO "Event Came From Read Function - %d\n",
		       atomic_read(&read_count));
		atomic_inc(&read_count);
		atomic_set(&wait_queue_flag, 0);
	}

	return 0;
}

static int __init wait_queue_init(void)
{
	struct proc_dir_entry *pe;

	printk(KERN_INFO "[Hello] mywaitqueue \n");
	pe = proc_create("test_wait_queue", 0644, NULL, &test_wait_queue_fops);
	if (!pe)
		return -ENOMEM;

	// Create the kernel thread with name "MyWaitThread"
	wait_thread = kthread_run(wait_function, NULL, "MyWaitThread");
	if (IS_ERR(wait_thread)) {
		proc_remove(pe);
		printk(KERN_ERR "Thread creation failed\n");
		return PTR_ERR(wait_thread);
	}

	return 0;
}

static void __exit wait_queue_exit(void)
{
	atomic_set(&wait_queue_flag, 2);
	wake_up_interruptible(&test_wait_queue);
	if (wait_thread)
		kthread_stop(wait_thread);
	printk(KERN_INFO "[Goodbye] mywaitqueue\n");
	remove_proc_entry("test_wait_queue", NULL);
}

module_init(wait_queue_init);
module_exit(wait_queue_exit);
MODULE_LICENSE("GPL");

/*
# insmod wait_queue.ko
[182363.054074] wait_queue: loading out-of-tree module taints kernel.
[182363.059294] [Hello] mywaitqueue
[182363.062260] Waiting For Event...
# rmmod wait_queue.ko
[182369.623671] Event Came From Exit Function
[182369.626703] [Goodbye] mywaitqueue
# insmod wait_queue.ko
[182373.599418] [Hello] mywaitqueue
[182373.602407] Waiting For Event...
# cat /proc/test_wait_queue
[182395.557732] Read function
read_count = 0
# [182395.560124] Event Came From Read Function - 0
[182395.562759] Waiting For Event...
# rmmod wait_queue.ko
[182402.369440] Event Came From Exit Function
[182402.372048] [Goodbye] mywaitqueue
# insmod wait_queue.ko
[182458.125664] [Hello] mywaitqueue
[182458.128377] Waiting For Event...
# cat /proc/test_wait_queue
[182481.416750] Read function
read_count = 0
[182481.418408] Event Came From Read Function - 0
[182481.422052] Waiting For Event...
# cat /proc/test_wait_queue
[182482.437127] Read function
read_count = 1
[182482.439690] Event Came From Read Function - 1
[182482.442564] Waiting For Event...
# cat /proc/test_wait_queue
[182483.667564] Read function
[182483.669334] Event Came From Read Function - 2
read_count = 2
[182483.672574] Waiting For Event...
# rmmod wait_queue.ko
[182485.976539] Event Came From Exit Function
[182485.979385] [Goodbye] mywaitqueue
*/
