#include <linux/delay.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/module.h>

static struct task_struct *task[NR_CPUS];

static void show_prio(void)
{
	struct task_struct *task = current;

	printk("%s pid:%d, nice:%d prio:%d static_prio:%d normal_prio:%d\n",
	       task->comm, task->pid, PRIO_TO_NICE(task->static_prio),
	       task->prio, task->static_prio, task->normal_prio);
}

static void print_cpu(char *str)
{
	preempt_disable();
	pr_info("%s cpu=%d.\n", str, smp_processor_id());
	preempt_enable();
}

static int thread_fun(void *data)
{
	do {
		print_cpu("SLEEP in Thread Function ");
		msleep_interruptible(2000);
		print_cpu("msleep over in Thread Function");
		print_cpu("running");
		show_prio();
	} while (!kthread_should_stop());
	return 0;
}

static int __init my_init(void)
{
	int count;
	print_cpu("Loading module");
	// 每个 cpu 遍历
	for_each_online_cpu(count) {
		task[count] =
			kthread_create(thread_fun, NULL, "kdemo/%d", count);
		if (!task[count]) {
			pr_info("Failed to generate a kernel thread\n");
			return -1;
		}
		kthread_bind(task[count], count);
		pr_info("About to wake up and run the thread for cpu=%d\n",
			count);
		// 启动运行 线程
		wake_up_process(task[count]);
		pr_info("Staring thread for cpu %d", count);
		print_cpu("on");
	}
	return 0;
}

static void __exit my_exit(void)
{
	int count;
	for_each_online_cpu(count) {
		pr_info(" Kill Thread %d", count);
		kthread_stop(task[count]);
		print_cpu("Kill was done on ");
	}
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Ben ShuShu");
MODULE_LICENSE("GPL v2");
