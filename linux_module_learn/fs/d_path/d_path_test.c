#include <linux/fs.h>
#include <linux/fs_struct.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/path.h>
#include <linux/pid.h>
#include <linux/sched.h>

#define TASK_PATH_MAX_LENGTH 13

// 内核模块初始化函数
static int __init demo_init(void)
{
	int ret = 0;
	struct qstr root_task_path;
	struct qstr current_task_path;

	char buf_1[TASK_PATH_MAX_LENGTH] = { 0 };
	// char *task_path_1 = NULL;

	char buf_2[TASK_PATH_MAX_LENGTH] = { 0 };
	char *task_path_2 = NULL;

	// 获取当前目录名
	current_task_path = current->fs->pwd.dentry->d_name;
	// 获取根目录
	root_task_path = current->fs->root.dentry->d_name;

	// 内核线程的 mm 成员为空，这里没做判断

	// 2.6.32 没有dentry_path_raw API
	// 获取文件全路径
	// task_path_1 = dentry_path_raw(current->mm->exe_file->f_path.dentry,
	// 			      buf_1, TASK_PATH_MAX_LENGTH);

	// 获取文件全路径
	// 调用d_path函数文件的路径时，应该使用返回的指针：task_path_2
	// ，而不是转递进去的参数buf：buf_2
	task_path_2 = d_path(&current->mm->exe_file->f_path, buf_2,
			     TASK_PATH_MAX_LENGTH);
	if (IS_ERR(task_path_2)) {
		ret = PTR_ERR(task_path_2);
		printk("Get path failed with error %d\n", ret);
		return -1;
	}

	printk("current path = %s\n", current_task_path.name);
	printk("root path = %s\n", root_task_path.name);
	printk("buf1 = [%s]\n", buf_1);
	printk("buf2 = [%s]\n", buf_2);
	// printk("task_path_1 = %s\n", task_path_1);
	printk("task_path_2 = %s\n", task_path_2);

	return -1;
}

module_init(demo_init);

MODULE_LICENSE("GPL");
