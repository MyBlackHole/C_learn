#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init demo_init(void)
{
	struct task_struct *p = NULL, *t = NULL;
	int syscall_num = 0;

	pr_info("%8s %8s %16s %8s %8s", "PID", "TGID", "COMM", "PRIO",
		"SYSCALL");
	// use Read-copy-update (RCU) to lock the list while we
	// traverse
	rcu_read_lock();
	for_each_process_thread(p, t) {
		// lock the process task_struct while we access fields
		task_lock(p);
		if (try_get_task_stack(t)) {
			syscall_num = task_pt_regs(t)->orig_ax;
		} else {
			syscall_num = -1;
		}
		pr_info("%8d %8d %16s %8d %8d", t->pid, t->tgid, t->comm,
			t->prio, syscall_num);

		/*// change the name of systemd process*/
		/*if (strcmp(t->comm, "systemd") == 0) {*/
		/*	strcpy(t->comm, "hidden");*/
		/*}*/
		task_unlock(p);
	}
	rcu_read_unlock();
	return 0;
}

static void __exit demo_exit(void)
{
	pr_info("Bye!\n");
}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");
