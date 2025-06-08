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
	char *kbuf;
	unsigned long order;
	unsigned long size;
	char *vm_buff;

	/* try __get_free_pages__ */
	for (size = PAGE_SIZE, order = 0; order < MAX_ORDER;
	     order++, size *= 2) {
		pr_info(" order=%2lu, pages=%5lu, size=%8lu ", order,
			size / PAGE_SIZE, size);
		kbuf = (char *)__get_free_pages(GFP_ATOMIC, order);
		if (!kbuf) {
			pr_err("... __get_free_pages failed\n");
			break;
		}
		pr_info("... __get_free_pages OK\n");
		pr_info("... kbuf %p\n", kbuf);
		free_pages((unsigned long)kbuf, order);
	}

	/* try kmalloc */
	for (size = PAGE_SIZE, order = 0; order < MAX_ORDER;
	     order++, size *= 2) {
		pr_info(" order=%2lu, pages=%5lu, size=%8lu ", order,
			size / PAGE_SIZE, size);
		kbuf = kmalloc((size_t)size, GFP_ATOMIC);
		if (!kbuf) {
			pr_err("... kmalloc failed\n");
			break;
		}
		pr_info("... kmalloc OK\n");
		pr_info("... kbuf %p\n", kbuf);
		kfree(kbuf);
	}

	/* try vmalloc */
	for (size = 4 * MB; size <= mem * MB; size += 4 * MB) {
		pr_info(" pages=%6lu, size=%8lu ", size / PAGE_SIZE, size / MB);
		vm_buff = vmalloc(size);
		if (!vm_buff) {
			pr_err("... vmalloc failed\n");
			break;
		}
		pr_info("... vmalloc OK\n");
		pr_info("... vm_buff %p\n", vm_buff);
		vfree(vm_buff);
	}

	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Module exit\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL v2");
