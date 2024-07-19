#include <linux/init.h>
#include <linux/kallsyms.h>
#include <linux/kprobes.h> // register_kprobe, unregister_kprobe
#include <linux/module.h>
#include <linux/version.h>

#define LOG_PREFIX "nfs hook remove: "

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

static int __init nfs_hook_init(void)
{
	printk(KERN_INFO "%s: init called\n", __func__);
	if (kallsyms_init() < 0) {
		return -EFAULT;
	}

	fptr_ref = (fptr)kallsyms_lookup_name_ref("nfsd4_remove");
	if (!fptr_ref) {
		printk("Didn't found nfsd4_remove\n");
		return 1;
	}

	printk("found nfsd4_remove = %p\n", fptr_ref);
	fptr_ref(0);

	return 0;
}

static void __exit nfs_hook_exit(void)
{
	printk(KERN_INFO "%s: exit called\n", __func__);
}

module_init(nfs_hook_init);
module_exit(nfs_hook_exit);

MODULE_AUTHOR("blackhole <1358244533@qq.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("nfs hook module test!");
