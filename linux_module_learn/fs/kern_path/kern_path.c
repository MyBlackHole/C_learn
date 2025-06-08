#include <linux/init.h>
#include <linux/module.h>
#include <linux/namei.h>
#include <linux/version.h>
#include <linux/fs.h>

#define LOG_PREFIX "path dentry test: "

#define FILE_TEST "/home/black/.bashrc"

#define TASK_PATH_MAX_LENGTH 512

static int __init path_init(void)
{
	struct path path;
	// char *pathname = NULL;
	// char buf[TASK_PATH_MAX_LENGTH] = { 0 };
	int ret = 0;

	printk(KERN_INFO "%s: init called\n", __func__);

	ret = kern_path(FILE_TEST, 0, &path);
	if (ret) {
		pr_info(LOG_PREFIX
			"failed to lookup path, error: %d pathname: %s\n",
			ret, FILE_TEST);
		return ret;
	}
	pr_info(LOG_PREFIX "lookup path, d_iname: %s\n", path.dentry->d_iname);

	// pathname = d_path(&path, buf, TASK_PATH_MAX_LENGTH);
	//
	// if (IS_ERR(pathname)) {
	// 	printk(LOG_PREFIX "d_path -> %ld\n", PTR_ERR(pathname));
	// 	path_put(&path);
	// 	return -1;
	// }
	//
	// pr_info(LOG_PREFIX "pathname: %s\n", pathname);

	// 释放 path 内存
	path_put(&path);

	return -1;
}

static void __exit path_exit(void)
{
	printk(KERN_INFO "%s: exit called\n", __func__);
}

module_init(path_init);
module_exit(path_exit);

MODULE_AUTHOR("blackhole <1358244533@qq.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("nfs hook module test!");
