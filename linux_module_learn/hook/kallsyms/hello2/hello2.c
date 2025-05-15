#include <linux/init.h>
#include <linux/module.h>

static int __init hello2_init(void)
{
	printk(KERN_INFO "%s: init called\n", __func__);
	return 0;
}

static void __exit hello2_exit(void)
{
	printk(KERN_INFO "%s: exit called\n", __func__);
}

int KKK_test_func(int flag)
{
	printk(KERN_INFO "FUNC: %s called, flag=%d\n", __func__, flag);
	return 0;
}
EXPORT_SYMBOL_GPL(KKK_test_func);

module_init(hello2_init);
module_exit(hello2_exit);

MODULE_AUTHOR("blackhole <1358244533@qq.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple test module!");
