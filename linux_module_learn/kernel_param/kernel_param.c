/**********************************************************
 * Author        : 梁金荣
 * Email         : Liangjinrong111@163.com
 * Last modified : 2019-09-14 13:00
 * Filename      : exnum.c
 * Description   : 模块初始化函数中求最大数（使用内核中的代码）
 * *******************************************************/

/**
 *必要的头文件
 */
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int aint;
static int bint;
module_param(aint, int, 0644);
MODULE_PARM_DESC(aint, "data of aint");
module_param(bint, int, 0644);
MODULE_PARM_DESC(bint, "data of bint");
/**
 *模块的初始化函数，模块的入口函数，加载模块，需超级用户权限
 */
static int __init lk_exnum(void)
{
	printk("Linux kernel param max number module is starting here！\n");
	printk("a = %d, b = %d\n", aint, bint);
	printk("max=%d\n", max(aint, bint));
	return 0;
}

/**
 *出口函数，卸载模块，需超级用户权限
 */
static void __exit lk_exit(void)
{
	printk("Linux kernel param max number moudle has exited!\n");
}

module_init(lk_exnum); // 内核入口点，调用初始化函数，包含在module.h中
module_exit(lk_exit); // 出口点
MODULE_LICENSE("GPL"); // 许可证
MODULE_AUTHOR("ljr"); // 作者（非必须）
MODULE_DESCRIPTION("Linux kernel param max number"); // 模块描述（非必须）
