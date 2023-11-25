#include <linux/init.h>
#include <linux/module.h>
#include <linux/namei.h>
#include <linux/version.h>

#define LOG_PREFIX "path dentry test: "

#define FILE_TEST \
    "/media/black/Data/Documents/C/linux_module_learn/fs/path/path_test.c"

static int __init path_init(void)
{
    struct path path;
    int ret = 0;

    printk(KERN_INFO "%s: init called\n", __func__);
    // const char* pathname;

    // pathname = kmalloc(PAGE_SIZE, GFP_KERNEL);

    ret = kern_path(FILE_TEST, 0, &path);
    if (ret)
    {
        pr_info(LOG_PREFIX "failed to lookup path, error: %d pathname: %s\n",
                ret, FILE_TEST);
        return ret;
    }

    pr_info(LOG_PREFIX "lookup path, d_iname: %s\n", path.dentry->d_iname);

    // 释放 path 内存
    path_put(&path);
    return 0;
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
