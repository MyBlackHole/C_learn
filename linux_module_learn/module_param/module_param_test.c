#include <linux/init.h>
#include <linux/module.h>

#define MY_MAJOR 0x09
static int global_val_test = MY_MAJOR;
module_param(global_val_test, int, 0644);

/*static int __init global_val_test_check(const char *val,*/
/*					struct kernel_param *kp)*/
/*{*/
/*	long int temp;*/
/*	if (kstrtol(val, 10, &temp) == 0 && temp >= 0 && temp <= 100) {*/
/*		return 0; // 参数有效*/
/*	}*/
/*	return -EINVAL; // 参数无效*/
/*}*/
/**/
/*module_param_cb(global_val_test, global_val_test_check, NULL, S_IRUGO);*/

// // 参数描述 modinfo module_param_test.ko
// MODULE_PARM_DESC(global_val_test, "global_val_test value");

static int __init module_param_init(void)
{
	printk(KERN_INFO "global_val_test = %d\n", global_val_test);
	if (global_val_test == 9)
		printk(KERN_INFO "hello my world enter\n");
	else
		printk(KERN_INFO "hello world enter\n");
	return 0;
}

static void __exit module_param_exit(void)
{
	printk(KERN_INFO "hello World exit\n");
}

module_init(module_param_init);
module_exit(module_param_exit);

MODULE_LICENSE("GPS");
