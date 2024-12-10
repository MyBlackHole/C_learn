#include "linux/printk.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/version.h>

#define KB (1024)

static int __init my_init(void)
{
	static void __iomem *va_addr;
	volatile u32 *va_data;

	pr_info("Module init\n");
	va_addr = ioremap(0x1e5a32048, 1024);

	if (va_addr == NULL) {
		pr_err("Failed to ioremap\n");
		return -ENOMEM;
	}
	pr_info("VA: 0x%p\n", va_addr);

	va_data = (volatile u32 *)va_addr;
	pr_info("Old Data: 0x%08x\n", *va_data);
	*va_data = 0x99999999;
	pr_info("New Data: 0x%08x\n", *va_data);
	iounmap(va_addr);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Module exit\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL v2");
