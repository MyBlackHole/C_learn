#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/idr.h>

struct node {
	char ch;
};

static int __init testidr_init(void)
{
	DEFINE_IDR(idr_mp);
	int idr_array[20];
	char str[] = "toosmallword";
	struct node item[20], *tmp;
	int index, key;

	idr_preload(GFP_KERNEL);

	for (index = 0; str[index]; ++index) {
		item[index].ch = str[index];
		idr_array[index] = idr_alloc_cyclic(&idr_mp, &item[index], 0,
						    INT_MAX, GFP_ATOMIC);
	}

	idr_for_each_entry(&idr_mp, tmp, key) {
		printk("%c's ID is %d\n", tmp->ch, key);
	}

	idr_replace(&idr_mp, &item[1], idr_array[0]);
	idr_remove(&idr_mp, idr_array[7]);

	for (index = 0; str[index]; ++index) {
		tmp = idr_find(&idr_mp, idr_array[index]);
		if (tmp) {
			printk("%c's ID is %d\n", tmp->ch, idr_array[index]);
		} else {
			printk("%d is not used\n", idr_array[index]);
		}
	}

	idr_for_each_entry(&idr_mp, tmp, key) {
		printk("%c's ID is %d\n", tmp->ch, key);
	}

	idr_preload_end();

	return 0;
}

static void __exit testidr_exit(void)
{
	printk("exit\n");
}

module_init(testidr_init);
module_exit(testidr_exit);
MODULE_LICENSE("GPL");
