/*
 * stack_overflow_demo.c - 内核栈溢出演示模块
 * 该模块展示了如何通过过度使用内核栈空间导致内核崩溃
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>

#define MODULE_NAME "stack_overflow_demo"

// 递归函数用于消耗栈空间
static void recursive_function(int depth)
{
	char buffer[1024]; // 分配1KB栈空间
	memset(buffer, 0, sizeof(buffer)); // 确保编译器不会优化掉缓冲区

	if (depth > 0) {
		// 打印当前栈使用情况
		printk(KERN_INFO
		       "%s: Recursion depth %d, stack approx: %lu bytes used\n",
		       MODULE_NAME, depth, depth * sizeof(buffer));
		recursive_function(depth - 1);
	}
}

// 模块初始化函数
static int __init stack_overflow_init(void)
{
	printk(KERN_INFO "%s: Loading kernel stack overflow demo module\n",
	       MODULE_NAME);

	// 尝试在中断上下文中触发栈溢出
	printk(KERN_INFO
	       "%s: Attempting to overflow kernel stack in process context\n",
	       MODULE_NAME);

	// 启动递归函数消耗栈空间
	recursive_function(12); // 12 * 1KB = 12KB > 8KB (典型内核栈大小)

	return 0;
}

// 模块退出函数
static void __exit stack_overflow_exit(void)
{
	printk(KERN_INFO "%s: Unloading module\n", MODULE_NAME);
}

module_init(stack_overflow_init);
module_exit(stack_overflow_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("black");
MODULE_DESCRIPTION("Kernel Stack Overflow Demonstration Module");
MODULE_VERSION("1.0");
