#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include "linux/slab.h"

static void kmalloc_oob_right(void)
{
	char *ptr;
	size_t size = 1024;

	/* 驱动中开启kasan必须开这个，否则没有报告打印 */
	bool multishot = kasan_save_enable_multi_shot();
	pr_info("kmalloc_oob_right: start\n");
	ptr = kmalloc(size, GFP_KERNEL);
	if (!ptr) {
		pr_err("kmalloc failed\n");
		return;
	}
	pr_info("ptr = %p\n", ptr);

	ptr[size] = 'a';
	pr_info("ptr[size] = %c\n", ptr[size]);
	kfree(ptr);

	kasan_restore_multi_shot(multishot);
}

static int __init kasan_hello(void)
{
	pr_info("kasan hello world!\n");
	kmalloc_oob_right();
	return 0;
}

static void __exit kasan_exit(void)
{
	pr_info("kasan good bye!\n");
}

module_init(kasan_hello);
module_exit(kasan_exit);

MODULE_LICENSE("GPL");
