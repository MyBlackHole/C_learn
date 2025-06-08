#include <linux/configfs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

struct simple_child {
	struct config_item item;
	int storeme;
};

static inline struct simple_child *to_simple_child(struct config_item *item)
{
	return container_of(item, struct simple_child, item);
}

static ssize_t simple_child_storeme_show(struct config_item *item, char *page)
{
	return sprintf(page, "%d\n", to_simple_child(item)->storeme);
}

static ssize_t simple_child_storeme_store(struct config_item *item,
					  const char *page, size_t count)
{
	struct simple_child *simple_child = to_simple_child(item);
	int ret;

	ret = kstrtoint(page, 10, &simple_child->storeme);
	if (ret)
		return ret;

	return count;
}

CONFIGFS_ATTR(simple_child_, storeme);

static struct configfs_attribute *simple_child_attrs[] = {
	&simple_child_attr_storeme,
	NULL,
};

static void simple_child_release(struct config_item *item)
{
	kfree(to_simple_child(item));
}

static struct configfs_item_operations simple_child_item_ops = {
	.release = simple_child_release,
};

static const struct config_item_type simple_child_type = {
	.ct_item_ops = &simple_child_item_ops,
	.ct_attrs = simple_child_attrs,
	.ct_owner = THIS_MODULE,
};

struct simple_children {
	struct config_group group;
};

static inline struct simple_children *
to_simple_children(struct config_item *item)
{
	return container_of(to_config_group(item), struct simple_children,
			    group);
}

static struct config_item *simple_children_make_item(struct config_group *group,
						     const char *name)
{
	struct simple_child *simple_child;

	simple_child = kzalloc(sizeof(struct simple_child), GFP_KERNEL);
	if (!simple_child)
		return ERR_PTR(-ENOMEM);

	config_item_init_type_name(&simple_child->item, name,
				   &simple_child_type);

	return &simple_child->item;
}

static ssize_t simple_children_description_show(struct config_item *item,
						char *page)
{
	return sprintf(
		page,
		"[02-simple-children]\n"
		"\n"
		"This subsystem allows the creation of child config_items.  These\n"
		"items have only one attribute that is readable and writeable.\n");
}

CONFIGFS_ATTR_RO(simple_children_, description);

static struct configfs_attribute *simple_children_attrs[] = {
	&simple_children_attr_description,
	NULL,
};

static void simple_children_release(struct config_item *item)
{
	kfree(to_simple_children(item));
}

static struct configfs_item_operations simple_children_item_ops = {
	.release = simple_children_release,
};

/*
 * Note that, since no extra work is required on ->drop_item(),
 * no ->drop_item() is provided.
 */
static struct configfs_group_operations simple_children_group_ops = {
	.make_item = simple_children_make_item,
};

static const struct config_item_type simple_children_type = {
	.ct_item_ops = &simple_children_item_ops,
	.ct_group_ops = &simple_children_group_ops,
	.ct_attrs = simple_children_attrs,
	.ct_owner = THIS_MODULE,
};

static struct config_group *
group_children_make_group(struct config_group *group, const char *name)
{
	struct simple_children *simple_children;

	simple_children = kzalloc(sizeof(struct simple_children), GFP_KERNEL);
	if (!simple_children)
		return ERR_PTR(-ENOMEM);

	config_group_init_type_name(&simple_children->group, name,
				    &simple_children_type);

	return &simple_children->group;
}

static ssize_t group_children_description_show(struct config_item *item,
					       char *page)
{
	return sprintf(
		page,
		"[03-group-children]\n"
		"\n"
		"This subsystem allows the creation of child config_groups.  These\n"
		"groups are like the subsystem simple-children.\n");
}

CONFIGFS_ATTR_RO(group_children_, description);

static struct configfs_attribute *group_children_attrs[] = {
	&group_children_attr_description,
	NULL,
};

static struct configfs_group_operations group_children_group_ops = {
	.make_group = group_children_make_group,
};

static const struct config_item_type group_children_type = {
	.ct_group_ops = &group_children_group_ops,
	.ct_attrs = group_children_attrs,
	.ct_owner = THIS_MODULE,
};

static struct configfs_subsystem group_children_subsys = {
    .su_group =
        {
            .cg_item =
                {
                    .ci_namebuf = "backup",
                    .ci_type    = &group_children_type,
                },
        },
};

static int __init backup_init(void)
{
	int ret;
	config_group_init(&group_children_subsys.su_group);
	mutex_init(&group_children_subsys.su_mutex);
	ret = configfs_register_subsystem(&group_children_subsys);
	if (ret) {
		pr_err("Error %d while registering subsystem %s\n", ret,
		       group_children_subsys.su_group.cg_item.ci_namebuf);
		goto out_unregister;
	}

out_unregister:
	return ret;
}

static void __exit backup_exit(void)
{
	configfs_unregister_subsystem(&group_children_subsys);
}

module_init(backup_init);
module_exit(backup_exit);
MODULE_LICENSE("GPL");
