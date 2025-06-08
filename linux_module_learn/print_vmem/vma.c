#include <linux/init.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/sched.h>

static int pid;
module_param(pid, int, 0644);

static void print_task_vma(struct task_struct *task)
{
	struct mm_struct *mms = task->mm;
	struct vm_area_struct *vma;
	int count = 0;
	unsigned long start;
	unsigned long end;
	unsigned long length;
	VMA_ITERATOR(vmi, mms, 0);

	pr_info("mm_struct addr = 0x%p\n", mms);

	mmap_read_lock(mms);
	pr_info("vmas:            vma        start          end        length\n");

	for_each_vma(vmi, vma) {
		count++;
		start = vma->vm_start;
		end = vma->vm_end;
		length = end - start;
		pr_info("%6d: %16p %12lx %12lx   %8ld\n", count, vma, start,
			end, length);
	}
	mmap_read_unlock(mms);
}

static int __init my_init(void)
{
	struct task_struct *task;
	/* if don't pass the pid over insmod, then use the current process */
	if (pid == 0) {
		task = current;
		pid = current->pid;
		pr_info("using current process\n");
	} else {
		task = pid_task(find_vpid(pid), PIDTYPE_PID);
	}
	if (!task) {
		return -1;
	}
	pr_info(" Examining vma's for pid=%d, command=%s\n", pid, task->comm);
	print_task_vma(task);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Module exit\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL v2");
