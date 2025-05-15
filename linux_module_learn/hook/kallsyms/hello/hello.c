#include <linux/init.h>
#include <linux/kallsyms.h>
#include <linux/kprobes.h> // register_kprobe, unregister_kprobe
#include <linux/module.h>
#include <linux/version.h>

#define LOG_PREFIX "hello: "

typedef unsigned long (*kallsyms_lookup_name_t)(const char *name);
static kallsyms_lookup_name_t kallsyms_lookup_name_ref;

typedef int (*fptr)(int);
static fptr fptr_ref;

int kallsyms_init(void)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 7, 0)
	// 大于 5.7.0 后 kallsyms_lookup_name 没有导出
	struct kprobe kln = { .symbol_name = "kallsyms_lookup_name" };
	if (register_kprobe(&kln) < 0) {
		return -EFAULT;
	}
	kallsyms_lookup_name_ref = (kallsyms_lookup_name_t)kln.addr;
	unregister_kprobe(&kln);
	if (!kallsyms_lookup_name_ref) {
		pr_err(LOG_PREFIX
		       "failed to lookup function kallsyms_lookup_name()\n");
		return -EFAULT;
	}
	return 0;
#else
	kallsyms_lookup_name_ref = kallsyms_lookup_name;
#endif
}

static int __init hello_init(void)
{
	printk(KERN_INFO "%s: init called\n", __func__);
	if (kallsyms_init() < 0) {
		return -EFAULT;
	}

	fptr_ref = (fptr)kallsyms_lookup_name_ref("KKK_test_func");
	if (!fptr_ref) {
		printk("Didn't found KKK_test_func\n");
		return 1;
	}

	printk("found KKK_test_func = %p\n", fptr_ref);
	fptr_ref(666);

	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_INFO "%s: exit called\n", __func__);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("blackhole <1358244533@qq.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple test module!");
