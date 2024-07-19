#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kobject.h>

static struct kobject *module_kobj;

#define DEMO_DIR_NAME "sysfs_demo"

static ssize_t file_kobj_add(struct kobject *kobj, struct kobj_attribute *attr,
			     const char *buf, size_t count)
{
	// int ret;
	// ret = file_add(buf);
	// if (ret < 0)
	// return ret;
	printk("%s", buf);
	return count;
}

static struct kobj_attribute file_kobj_add_attribute =
	__ATTR(add_file, 0200, NULL, file_kobj_add);

static struct attribute *file_attrs[] = { &file_kobj_add_attribute.attr, NULL };

static struct attribute_group file_attr_group = {
	.name = "fs_file",
	.attrs = file_attrs,
};

static int __init demo_init(void)
{
	int ret = 0;
	printk("sysfs_init\n");
	module_kobj = kobject_create_and_add(DEMO_DIR_NAME, kernel_kobj);
	if (!module_kobj) {
		return -ENOMEM;
	}

	ret = sysfs_create_group(module_kobj, &file_attr_group);
	if (ret) {
		goto failed;
	}

	return 0;

failed:
	kobject_put(module_kobj);
	return ret;
}

static void __exit demo_exit(void)
{
	printk("sysfs_exit\n");
	if (module_kobj) {
		kobject_put(module_kobj);
	}
}

module_init(demo_init);
module_exit(demo_exit);

MODULE_LICENSE("GPL");
