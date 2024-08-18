#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/file.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kallsyms.h>
#include <linux/delay.h>
#include "arch.h"

static unsigned long *__sys_call_table;

typedef long (*syscall_fn_t)(const struct pt_regs *regs);
static syscall_fn_t orig_open;
static syscall_fn_t orig_openat;
static syscall_fn_t orig_write;

static unsigned int cr0 = 0;
unsigned int clear_and_return_cr0(void)
{
	unsigned int cr0 = 0;
	unsigned int ret;
	asm volatile("movq %%cr0, %%rax" : "=a"(cr0));
	ret = cr0;
	cr0 &= 0xfffeffff;
	asm volatile("movq %%rax, %%cr0" ::"a"(cr0));
	return ret;
}

void setback_cr0(unsigned int val)
{
	asm volatile("movq %%rax, %%cr0" ::"a"(val));
}

/*unsigned long cr0;*/
/*static inline void write_cr0_forced(unsigned long val)*/
/*{*/
/*	unsigned long __force_order;*/
/**/
/*	asm volatile("mov %0, %%cr0" : "+r"(val), "+m"(__force_order));*/
/*}*/
/**/
/*static inline void protect_memory(void)*/
/*{*/
/*	write_cr0_forced(cr0);*/
/*}*/
/*static inline void unprotect_memory(void)*/
/*{*/
/*	write_cr0_forced(cr0 & ~X86_CR0_WP);*/
/*}*/

asmlinkage long open_hook(const struct pt_regs *regs)
{
	const char __user *filename = NULL;
	int filename_len = 0;
	char filename_buf[504] = { 0 };
	filename = (const char __user *)PT_REGS_PARM1(regs);

	filename_len = strncpy_from_user(filename_buf, filename,
					 sizeof(filename_buf) - 1);

	return orig_open(regs);
}

asmlinkage long openat_hook(const struct pt_regs *regs)
{
	const char __user *filename = NULL;
	int filename_len = 0;
	char filename_buf[504] = { 0 };
	filename = (const char __user *)PT_REGS_PARM2(regs);

	filename_len = strncpy_from_user(filename_buf, filename,
					 sizeof(filename_buf) - 1);

	return orig_openat(regs);
}

#define KERNEL_LOG_FILE "/tmp/messages"
#define KERNEL_CONSOLE_FILE "/dev/console"


asmlinkage long write_hook(const struct pt_regs *regs)
{
	unsigned int fd = -1;
	struct file *myfile = NULL;
	char path[100] = { '\0' };
	/*struct files_struct *files = NULL;*/
	/*struct task_struct *task = current;*/
	char *ppath = path;
	fd = PT_REGS_PARM1(regs);

	myfile = fget(fd);
	if (myfile) {
		ppath = d_path(&(myfile->f_path), ppath, 100);
		// 排除内核日志文件路径
		// 避免死循环
		if (ppath && strncmp(KERNEL_LOG_FILE, ppath,
				     strlen(KERNEL_LOG_FILE)) == 0) {
			goto original__;
		}
		if (ppath && strncmp(KERNEL_CONSOLE_FILE, ppath,
				     strlen(KERNEL_CONSOLE_FILE)) == 0) {
			goto original__;
		}
		printk("path:%s\n", ppath);
	}
	/*if (fd > 2) {*/
	/*	files = task->files;*/
	/*	if (fd < files->fdt->fd->max_fds) {*/
	/*		myfile = files->fdt->fd[fd];*/
	/*		if (myfile) {*/
	/*			ppath = d_path(&(myfile->f_path), ppath, 100);*/
	/*			printk("path:%s\n", ppath);*/
	/*		}*/
	/*	}*/
	/*}*/
original__:
	return orig_write(regs);
}

static int __init open_hook_init(void)
{
	__sys_call_table =
		(unsigned long *)kallsyms_lookup_name("sys_call_table");
	if (!__sys_call_table)
		return -EINVAL;

	orig_open = (syscall_fn_t)__sys_call_table[__NR_open];
	orig_openat = (syscall_fn_t)__sys_call_table[__NR_openat];
	orig_write = (syscall_fn_t)__sys_call_table[__NR_write];

	cr0 = clear_and_return_cr0();
	__sys_call_table[__NR_open] = (unsigned long)open_hook;
	__sys_call_table[__NR_openat] = (unsigned long)openat_hook;
	__sys_call_table[__NR_write] = (unsigned long)write_hook;
	setback_cr0(cr0);
	printk("open_hook_init\n");

	return 0;
}

static void __exit open_hook_exit(void)
{
	cr0 = clear_and_return_cr0();
	__sys_call_table[__NR_open] = (unsigned long)orig_open;
	__sys_call_table[__NR_openat] = (unsigned long)orig_openat;
	__sys_call_table[__NR_write] = (unsigned long)orig_write;
	setback_cr0(cr0);
	printk("open_hook_exit\n");
}

module_init(open_hook_init);
module_exit(open_hook_exit);

MODULE_LICENSE("GPL");
