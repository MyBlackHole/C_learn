#include "asm/syscall.h"
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/file.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/kallsyms.h>
#include <linux/delay.h>

#include "arch.h"

DEFINE_STATIC_SRCU(srcu);
static unsigned long *__sys_call_table;

typedef long (*syscall_fn_t)(const struct pt_regs *regs);
static syscall_fn_t orig_open;
static syscall_fn_t orig_openat;
static syscall_fn_t orig_write;
static syscall_fn_t orig_unlink;
static syscall_fn_t orig_open_tmp;
static syscall_fn_t orig_openat_tmp;
static syscall_fn_t orig_write_tmp;

/*#if 0*/
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 7, 0)
#include <linux/kprobes.h>

typedef unsigned long (*kallsyms_lookup_name_t)(const char *name);
kallsyms_lookup_name_t my_kallsyms_lookup_name;

static char symbol[KSYM_NAME_LEN] = "kallsyms_lookup_name";
module_param_string(symbol, symbol, KSYM_NAME_LEN, 0644);

/* For each probe you need to allocate a kprobe structure */
static struct kprobe kp = {
	.symbol_name = symbol,
};

unsigned long lookup_name(const char *name);
unsigned long lookup_name(const char *name)
{
	int ret = 0;
	ret = register_kprobe(&kp);
	if (ret < 0) {
		printk("register_kprobe error, %d:[%p]\n", ret, kp.addr);
		return 0;
	}
	unregister_kprobe(&kp);
	my_kallsyms_lookup_name = (kallsyms_lookup_name_t)kp.addr;
	return my_kallsyms_lookup_name(name);
}
#else
unsigned long lookup_name(const char *name);
unsigned long lookup_name(const char *name)
{
	return kallsyms_lookup_name(name);
}
#endif

static unsigned int cr0 = 0;
unsigned int clear_and_return_cr0(void);
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

void setback_cr0(unsigned int val);
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

asmlinkage long open_hook(const struct pt_regs *regs);
asmlinkage long open_hook(const struct pt_regs *regs)
{
	const char __user *filename = NULL;
	int filename_len = 0;
	char filename_buf[504] = { 0 };
	filename = (const char __user *)PT_REGS_PARM1(regs);

	filename_len = strncpy_from_user(filename_buf, filename,
					 sizeof(filename_buf) - 1);

	printk("open path:%s\n", filename);
	return orig_open(regs);
}

asmlinkage long openat_hook(const struct pt_regs *regs);
asmlinkage long openat_hook(const struct pt_regs *regs)
{
	int ret = 0;
	int id = 0;
	const char __user *filename = NULL;
	int filename_len = 0;
	char filename_buf[504] = { 0 };
	char *file_path = "/home/black/wdg.log";
	id = srcu_read_lock(&srcu);

	filename = (const char __user *)PT_REGS_PARM2(regs);

	filename_len = strncpy_from_user(filename_buf, filename,
					 sizeof(filename_buf) - 1);

	printk("openat_hook path:%s\n", filename);

	if (memcmp(filename_buf, file_path, strlen(file_path)) == 0) {
		printk(KERN_INFO "hook_openat() called");
		ssleep(20);
	}
	ret = orig_openat(regs);
	srcu_read_unlock(&srcu, id);
	return ret;
}

#define KERNEL_LOG_FILE "/tmp/messages"
#define KERNEL_CONSOLE_FILE "/dev/console"

asmlinkage long write_hook(const struct pt_regs *regs);
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
	// int ret = 0;
	// struct pt_regs regs = { 0 };
	// char *path = "/home/black/wdg.log.bak";

	__sys_call_table = (unsigned long *)lookup_name("sys_call_table");
	if (!__sys_call_table) {
		printk("__sys_call_table error\n");
		return -EINVAL;
	}

	printk("__sys_call_table:%lx\n", (unsigned long)__sys_call_table);

	orig_open = (syscall_fn_t)__sys_call_table[__NR_open];
	orig_openat = (syscall_fn_t)__sys_call_table[__NR_openat];
	orig_write = (syscall_fn_t)__sys_call_table[__NR_write];
	orig_unlink = (syscall_fn_t)__sys_call_table[__NR_unlink];
	printk("orig_open:%lx, orig_openat:%lx, orig_write:%lx\n",
	       (unsigned long)orig_open, (unsigned long)orig_openat,
	       (unsigned long)orig_write);

	cr0 = clear_and_return_cr0();
	/*cr0 = read_cr0();*/
	__sys_call_table[__NR_open] = (unsigned long)open_hook;
	__sys_call_table[__NR_openat] = (unsigned long)openat_hook;
	__sys_call_table[__NR_write] = (unsigned long)write_hook;

	orig_open_tmp = (syscall_fn_t)__sys_call_table[__NR_open];
	orig_openat_tmp = (syscall_fn_t)__sys_call_table[__NR_openat];
	orig_write_tmp = (syscall_fn_t)__sys_call_table[__NR_write];

	printk("open_hook:%lx, openat_hook:%lx, write_hook:%lx\n",
	       (unsigned long)open_hook, (unsigned long)openat_hook,
	       (unsigned long)write_hook);

	printk("orig_open_tmp:%lx, orig_openat_tmp:%lx, orig_write_tmp:%lx\n",
	       (unsigned long)orig_open_tmp, (unsigned long)orig_openat_tmp,
	       (unsigned long)orig_write_tmp);
	setback_cr0(cr0);
	printk("open_hook_init\n");

	// PT_REGS_PARM1(&regs) = (unsigned long)path;
	// ret = (*orig_unlink)(&regs);
	// if (ret < 0) {
	// 	printk("orig_unlink error:%d\n", ret);
	// } else {
	// 	printk("orig_unlink success, ret:%d\n", ret);
	// }
	return 0;
}

static void __exit open_hook_exit(void)
{
	cr0 = clear_and_return_cr0();
	__sys_call_table[__NR_open] = (unsigned long)orig_open;
	__sys_call_table[__NR_openat] = (unsigned long)orig_openat;
	__sys_call_table[__NR_write] = (unsigned long)orig_write;
	setback_cr0(cr0);
	synchronize_srcu(&srcu);
	printk("open_hook_exit\n");
}

module_init(open_hook_init);
module_exit(open_hook_exit);

MODULE_LICENSE("GPL");
