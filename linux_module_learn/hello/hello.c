#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include "linux/slab.h"

static int a = 10;

__attribute__((optimize("O0"))) static int __init hello_init(void)
{
	pr_info("hello world!\n");
	const void *ptr = 0x0000000087de68e7;
	pr_info("%ld!\n", PTR_ERR(ptr));
	pr_info("a = %d!\n", a);

	// char *buf_path;
	// buf_path = kmalloc(12, 0);
	// if (buf_path == NULL)
	// {
	//     printk("kmalloc failed\n");
	//     return -ENOMEM;
	// }
	// for (int i = 0; i < 516; i++)
	// {
	//     buf_path[i] = 'a';
	// }
	// printk("%s\n", buf_path);
	// printk("%c\n", buf_path[515]);
	// kfree(buf_path);
	return 0;
}
static void __exit hello_exit(void)
{
	printk("good bye!\n");
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
