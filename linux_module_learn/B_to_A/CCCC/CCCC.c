#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>

static int global_var = 1;
// int global_var = 1;
// EXPORT_SYMBOL(global_var);

static int __init aaaa_hello(void)
{
	printk("aaaa_hello\n");
	printk("global_var[%d]\n", global_var);
	return 0;
}

static void __exit aaaa_exit(void)
{
	// int index = 0;
	// while (global_var)
	// {
	//     ssleep(1);
	//     printk("%d sys hook count: %d", __LINE__, index);
	//     index++;
	// }
	printk("aaaa_exit\n");
	printk("global_var[%d]\n", global_var);
}

module_init(aaaa_hello);
module_exit(aaaa_exit);
MODULE_LICENSE("GPL");
