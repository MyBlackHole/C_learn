#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init tasks_init(void)
{
	pr_info("%8s %8s %16s %8s", "PID", "TGID", "COMM", "PRIO");
	struct task_struct *p = NULL, *t = NULL;

	// use Read-copy-update (RCU) to lock the list while we
	// traverse
	rcu_read_lock();
	for_each_process_thread(p, t) {
		// lock the process task_struct while we access fields
		task_lock(p);
		pr_info("%8d %8d %16s %8d", t->pid, t->tgid, t->comm, t->prio);

		// change the name of systemd process
		if (strcmp(t->comm, "systemd") == 0) {
			strcpy(t->comm, "hidden");
		}
		task_unlock(p);
	}
	rcu_read_unlock();
	return 0;
}

static void __exit tasks_exit(void)
{
	pr_info("Bye!\n");
}

module_init(tasks_init);
module_exit(tasks_exit);
MODULE_LICENSE("GPL");
