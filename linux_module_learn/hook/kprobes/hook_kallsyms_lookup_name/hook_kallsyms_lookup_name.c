#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kallsyms.h>
#include <linux/kprobes.h>

static struct kprobe kp = {
	.symbol_name = "kallsyms_lookup_name",
};

unsigned long (*kallsyms_lookup_name_fun)(const char *name);

int find_kallsyms_lookup_name(void);
int find_kallsyms_lookup_name(void)
{
	int ret;
	ret = register_kprobe(&kp);
	if (ret < 0) {
		printk(KERN_INFO "register_kprobe failed, error:%d\n", ret);
		return ret;
	}
	printk(KERN_INFO "kallsyms_lookup_name addr: %p\n", kp.addr);
	kallsyms_lookup_name_fun = (void *)kp.addr;
	unregister_kprobe(&kp);
	return ret;
}

static int __init hook_kallsyms_lookup_name_init(void)
{
	int ret;
	ret = find_kallsyms_lookup_name();
	if (ret < 0) {
		printk(KERN_INFO "find kallsyms_lookup_name failed\n");
		return ret;
	}
	static typeof(&print_modules) print_modules_p;
	print_modules_p = (typeof(&print_modules))kallsyms_lookup_name_fun(
		"print_modules");
	//打印内核加载的模块
	print_modules_p();
	printk(KERN_INFO "print_modules_p: 0x%p", print_modules_p);

	return 0;
}

static void __exit hook_kallsyms_lookup_name_exit(void)
{
	return;
}

module_init(hook_kallsyms_lookup_name_init);
module_exit(hook_kallsyms_lookup_name_exit);
MODULE_LICENSE("GPL");
