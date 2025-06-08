#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/version.h>

#define MB (1024 * 1024)

#define size (1 * MB)

char *kbuf;
static int __init my_init(void)
{
	kbuf = kmalloc((size_t)size, GFP_ATOMIC);
	if (!kbuf) {
		pr_err("... kmalloc failed, err=%d\n", -ENOMEM);
		return 1;
	}
	memset(kbuf, 0, size);
	kbuf[0] = 'w';
	kbuf[1] = 'd';
	kbuf[2] = 'g';
	pr_info("... kmalloc success, size=%d, addr=%lx\n", size,
		(unsigned long)kbuf);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Module exit\n");
	if (kbuf) {
		pr_info("kbuf is %s\n", kbuf);
		kfree(kbuf);
	}
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL v2");

// output:
//
// # insmod kmalloc_mm.ko
// [  236.180480] ... kmalloc success, size=1048576, addr=ffff88822d600000
// # rmmod kmalloc_mm.ko
// [  260.863802] Module exit
// [  260.865016] kbuf is wdg
