#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/xarray.h>

struct my_data {
	int index;
	char name[20];
};
typedef struct my_data my_data_t;
// 定义一个全局的XArray
DEFINE_XARRAY(my_xarray);

static void insert_data(int index, const char *name)
{
	my_data_t *data;
	data = kmalloc(sizeof *data, GFP_KERNEL);
	data->index = index;
	strncpy(data->name, name, sizeof(data->name));

	xa_store(&my_xarray, index, data, GFP_KERNEL);
}
static void remove_data(int index)
{
	my_data_t *data = xa_erase(&my_xarray, index);
	if (data) {
		kfree(data);
	}
}
static my_data_t *get_data(int index)
{
	return xa_load(&my_xarray, index);
}
static int __init xarray_example_init(void)
{
	my_data_t *data;
	unsigned long index;

	pr_info("xarray_example: Initializing XArray example module\n");
	insert_data(1, "John");
	insert_data(2, "Alice");
	insert_data(3, "Bob");
	insert_data(4, "Steve");
	data = get_data(2);
	if (data) {
		pr_info("xarray_example: ID: %d, Name: %s\n", data->index,
			data->name);
	}
	pr_info("xarray_example: before remove data 3");
	xa_for_each(&my_xarray, index, data) {
		pr_info("index = %ld, data = %p, data->id = %d, data->name = %s\n",
			index, data, data->index, data->name);
	}
	remove_data(3);
	pr_info("xarray_example: after remove data 3\n");
	xa_for_each(&my_xarray, index, data) {
		pr_info("index = %ld, data = %p, data->id = %d, data->name = %s\n",
			index, data, data->index, data->name);
	}
	return 0;
}

static void __exit xarray_example_exit(void)
{
	my_data_t *data;
	unsigned long index;

	pr_info("xarray_example: Cleaning up XArray example module\n");
	xa_for_each(&my_xarray, index, data) {
		xa_erase(&my_xarray, index);
		kfree(data);
	}
}

module_init(xarray_example_init);
module_exit(xarray_example_exit);
MODULE_LICENSE("GPL");
