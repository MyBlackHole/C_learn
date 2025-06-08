#include <linux/init.h>
#include <linux/module.h>
#include <linux/radix-tree.h>
#include <linux/slab.h>

struct element {
	unsigned long key;
	unsigned char data[16];
};

RADIX_TREE(test_tree, GFP_KERNEL);

static int __init test_init(void)
{
	struct element *e, *e1, *e2, *e3;
	struct radix_tree_iter iter;
	void **slot;

	e1 = kmalloc(sizeof(struct element) * 3, GFP_KERNEL);
	if (!e1) {
		pr_info("kmalloc failed\n");
		return -ENOMEM;
	}
	e2 = e1 + 1;
	e3 = e2 + 1;

	e1->key = 100;
	sprintf(e1->data, "element 1");
	e2->key = 2000;
	sprintf(e2->data, "element 2");
	e3->key = 33333;
	sprintf(e3->data, "element 3");

	radix_tree_insert(&test_tree, e1->key, e1);

	e = radix_tree_lookup(&test_tree, 500L);
	if (!e) {
		pr_info("radix_tree_lookup %ld failed\n", 500L);
	}

	radix_tree_insert(&test_tree, e2->key, e2);
	e = radix_tree_lookup(&test_tree, 2000L);
	if (!e) {
		pr_info("radix_tree_lookup failed\n");
	}
	pr_info("radix_tree_lookup: %ld, %s\n", e->key, e->data);

	radix_tree_preload(GFP_KERNEL);
	radix_tree_insert(&test_tree, e3->key, e3);
	radix_tree_preload_end();

	e = radix_tree_delete(&test_tree, 2000L);
	if (!e) {
		pr_info("radix_tree_delete failed\n");
	}
	pr_info("radix_tree_delete: %ld, %s\n", e->key, e->data);

	radix_tree_for_each_slot(slot, &test_tree, &iter, 0) {
		e = *slot;
		pr_info("radix_tree_for_each_slot: %ld, %s\n", e->key, e->data);
	}

	radix_tree_for_each_slot(slot, &test_tree, &iter, 0) {
		e = *slot;
		radix_tree_delete(&test_tree, e->key);
	}
	kfree(e1);

	return 0;
}

static void __exit test_exit(void)
{
}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("test routine for Linux radix tree");
