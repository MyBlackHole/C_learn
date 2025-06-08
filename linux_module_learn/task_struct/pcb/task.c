#include <linux/fdtable.h>
#include <linux/fs_struct.h>
#include <linux/init.h>
#include <linux/init_task.h>
#include <linux/kernel.h>
#include <linux/mm_types.h>
#include <linux/module.h>
#include <uapi/linux/sched.h>

static int __init traverse_pcb(void)
{
	int i;
	struct task_struct *task, *p;
	struct list_head *pos;
	struct files_struct *files;
	struct fdtable *fdt;
	struct file *file;
	char *buf_path;
	int count = 0;
	printk("Printf process'message begin:\n");
	task = &init_task;
	buf_path = kmalloc(512, 0);

	// 使用list_for_each宏来遍历进程链表
	list_for_each(pos, &task->tasks) {
		// 指向当前进程的task_struct结构
		p = list_entry(pos, struct task_struct, tasks);

		count++;
		printk("\n\n");
		/*
		 * 打印task_struct中的字段
		 *
		 * pid: 进程的pid号
		 * state:进程的状态
		 * prio:动态优先级
		 * static_prio:静态优先级
		 * parent.pid:父进程的pid号；
		 * count:文件系统信息,文件被使用的次数
		 * umask:进程权限位的默认设置;
		 *
		 * 使用atomic_read原子操作是为了(p->files)->count字段计数不被打断
		 */
		printk("comm:%s; pid:%d; prio:%d; static_prio:%d; "
		       "parent'pid:%d; count:%d; umask:%d;",
		       p->comm, p->pid, p->prio, p->static_prio,
		       (p->parent)->pid, atomic_read((&(p->files)->count)),
		       (p->fs)->umask);

		// 打印进程地址空间的信息
		if ((p->mm) != NULL) {
			// total_vm：线性区总的页数
			printk("total_vm:%ld;", (p->mm)->total_vm);
		}

		files = task->files;
		if (files != NULL) {
			fdt = files->fdt;
			while (fdt != NULL) {
				for (i = 0; i < NR_OPEN_DEFAULT; i++) {
					file = fdt->fd[i];
					if (file == NULL) {
						continue;
					}
					if (file->f_path.dentry != NULL &&
					    file->f_path.dentry->d_name.name !=
						    NULL) {
						printk("NAME:%s",
						       file->f_path.dentry
							       ->d_name.name);
						if (file->f_path.mnt != NULL) {
							buf_path = d_path(
								&(file->f_path),
								buf_path, 512);
							if (buf_path != NULL) {
								printk("%s",
								       buf_path);
							}
						}
					}
				}
			}
		}
	}
	kfree(buf_path);
	printk("进程的个数：%d\n", count);
	return 0;
}

static void __exit end_pcb(void)
{
	printk("traverse pcb is end.");
}

module_init(traverse_pcb);
module_exit(end_pcb);
MODULE_LICENSE("GPL");
