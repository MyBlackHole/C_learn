#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/rbtree.h>
#include <linux/slab.h>

MODULE_AUTHOR("ljr");
MODULE_DESCRIPTION("Using rbtree");
MODULE_LICENSE("GPL");

struct mytype {
	struct rb_node node;
	int key;
};

struct rb_root mytree = RB_ROOT;

struct mytype *my_search(struct rb_root *root, int new)
{
	struct rb_node *node = root->rb_node;

	while (node) {
		struct mytype *data = container_of(node, struct mytype, node);

		if (data->key > new) {
			node = node->rb_left;
		} else if (data->key < new) {
			node = node->rb_right;
		} else {
			return data;
		}
	}
	return NULL;
}

int my_insert(struct rb_root *root, struct mytype *data)
{
	struct rb_node **new = &(root->rb_node);
	struct rb_node *parent = NULL;

	/* Figure out where to put new node */
	while (*new) {
		struct mytype *this = container_of(*new, struct mytype, node);

		parent = *new;
		if (this->key > data->key) {
			new = &((*new)->rb_left);
		} else if (this->key < data->key) {
			new = &((*new)->rb_right);
		} else {
			return -1;
		}
	}

	/* Add new node and rebalance tree. */
	rb_link_node(&data->node, parent, new);
	rb_insert_color(&data->node, root);

	return 0;
}

static int __init my_init(void)
{
	int iii;
	struct mytype *data;
	struct rb_node *node;
	printk("The rbtree kernel is starting!\n");
	for (iii = 0; iii < 10; iii++) {
		data = kmalloc(sizeof(struct mytype), GFP_KERNEL);
		data->key = iii + 1;
		my_insert(&mytree, data);
	}

	/*list all tree*/
	for (node = rb_first(&mytree); node; node = rb_next(node)) {
		printk("data=%d\n", rb_entry(node, struct mytype, node)->key);
	}

	return 0;
}

static void __exit my_exit(void)
{
	struct mytype *data;
	struct rb_node *node;
	printk("The rbtree kernel is exiting!\n");
	for (node = rb_first(&mytree); node; node = rb_next(node)) {
		data = rb_entry(node, struct mytype, node);
		if (data) {
			rb_erase(&data->node, &mytree);
			kfree(data);
		}
	}
}
module_init(my_init);
module_exit(my_exit);
