#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include "linux/slab.h"

__attribute__((optimize("O0"))) static int __init lk_hello(void)
{
	printk("hello world!\n");
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
static void __exit lk_exit(void)
{
	printk("good bye!\n");
}
module_init(lk_hello);
module_exit(lk_exit);
MODULE_LICENSE("GPL");
