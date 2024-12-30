#include "linux/printk.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/version.h>

static int mem = 64;

#define MB (1024 * 1024)

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
#define MAX_ORDER 12
#endif

static int __init my_init(void)
{
	unsigned long size = mem * MB;
	char *vm_buff;

	/* try vmalloc */
	vm_buff = vmalloc(size);
	if (!vm_buff) {
		pr_err("... vmalloc failed\n");
		return -ENOMEM;
	}
	pr_info("... vmalloc OK\n");
	pr_info("... vm_buff %p\n", vm_buff);
	vfree(vm_buff);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Module exit\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL v2");
