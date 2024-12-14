#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/version.h>

#define MB (1024 * 1024)

#define size (10 * MB)

char *kbuf;
static int __init my_init(void)
{
	kbuf = kmalloc((size_t)size, GFP_ATOMIC);
	if (!kbuf) {
		pr_err("... kmalloc failed, err=%d\n", -ENOMEM);
		return 1;
	}
	pr_info("... kmalloc success, size=%d, addr=%lx\n", size,
		(unsigned long)kbuf);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Module exit\n");
	if (kbuf) {
		kfree(kbuf);
	}
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL v2");
