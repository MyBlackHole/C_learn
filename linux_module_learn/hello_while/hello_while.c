#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>

static int __init lk_hello(void)
{
	printk("hello world!\n");
	return 0;
}

static void __exit lk_exit(void)
{
	int index = 0;
	while (1) {
		ssleep(1);
		printk("%d sys hook count: %d", __LINE__, index);
		index++;
	}
	printk("good bye!\n");
}
module_init(lk_hello);
module_exit(lk_exit);
MODULE_LICENSE("GPL");
