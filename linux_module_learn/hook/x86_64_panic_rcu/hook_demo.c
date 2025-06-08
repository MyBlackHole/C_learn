#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/file.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/kallsyms.h>
#include <linux/delay.h>
#include "arch.h"

static unsigned long *__sys_call_table;

typedef long (*syscall_fn_t)(const struct pt_regs *regs);
static syscall_fn_t orig_openat;

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

#define WDG_FILE1 "/home/black/wdg1.log"
#define WDG_FILE2 "/home/black/wdg2.log"

asmlinkage long openat_hook(const struct pt_regs *regs);
asmlinkage long openat_hook(const struct pt_regs *regs)
{
	int *panic = NULL;
	const char __user *filename = NULL;
	int filename_len = 0;
	char filename_buf[504] = { 0 };
	rcu_read_lock();

	filename = (const char __user *)PT_REGS_PARM2(regs);

	filename_len = strncpy_from_user(filename_buf, filename,
					 sizeof(filename_buf) - 1);

	rcu_read_unlock();
	if (memcmp(filename_buf, WDG_FILE1, strlen(WDG_FILE1)) == 0) {
		printk("openat_hook path:%s\n", filename);
		ssleep(10);
	}
	if (memcmp(filename_buf, WDG_FILE2, strlen(WDG_FILE2)) == 0) {
		printk("openat_hook path:%s\n", filename);
		ssleep(1);
		*panic = 10;
	}
	return orig_openat(regs);
}

static int __init open_hook_init(void)
{
	__sys_call_table = (unsigned long *)lookup_name("sys_call_table");
	if (!__sys_call_table) {
		printk("__sys_call_table error\n");
		return -EINVAL;
	}

	orig_openat = (syscall_fn_t)__sys_call_table[__NR_openat];

	cr0 = clear_and_return_cr0();
	__sys_call_table[__NR_openat] = (unsigned long)openat_hook;

	printk("__NR_openat:%lx\n", __sys_call_table[__NR_openat]);
	setback_cr0(cr0);
	printk("open_hook_init\n");

	return 0;
}

static void __exit open_hook_exit(void)
{
	cr0 = clear_and_return_cr0();
	__sys_call_table[__NR_openat] = (unsigned long)orig_openat;
	setback_cr0(cr0);
	synchronize_rcu();
	printk("open_hook_exit\n");
}

module_init(open_hook_init);
module_exit(open_hook_exit);

MODULE_LICENSE("GPL");
