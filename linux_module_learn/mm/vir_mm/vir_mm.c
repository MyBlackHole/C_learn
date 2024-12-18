#include "linux/printk.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/version.h>

static unsigned long mem_addr = 0;
module_param(mem_addr, ulong, 0600);

static int __init my_init(void)
{
	unsigned long *ptr = mem_addr;

	if (ptr == 0) {
		return -EINVAL;
	}
	pr_info("ptr is %s\n", (char *)ptr);
	*ptr = 0x99999999;
	pr_info("ptr is %s\n", (char *)ptr);
	pr_info("New Data: 0x%08lx\n", *ptr);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Module exit\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL v2");

// output:
//
// # insmod hw_breakpoint.ko
// [  300.166282] hw_breakpoint hello world!
// [  300.168295] ptr = 0000000077b3e6e9
// [  300.170003] ptr = 0xffff8881e5ca5608
// [  300.172099] physical address = 0x1e5ca5608
// [  300.174300] physical address = 0x1e5ca5608
// [  300.177127] register_wide_hw_breakpoint success
// # insmod phy_mm.ko
// [  336.737332] Module init
// [  336.739025] VA: 0x00000000fdfb87db
// [  336.740912] Old Data: 0x44332211
// [  336.743147] New Data: 0x99999999
//
// 2 output:
//
// # insmod kmalloc_mm.ko
// [  265.194533] ... kmalloc success, size=1048576, addr=ffff88822d600000
//
// # insmod vir_mm.ko
// [  511.652841] Module init
// [  511.653849] ptr is wdg
// [  511.654828] ptr is
// [  511.655987] New Data: 0x99999999
// # rmmod kmalloc_mm.ko
// [  536.052739] Module exit
// [  536.054408] kbuf is
//
//
// 3 output:
//
//
// insmod vir_mm.ko mem_addr=18446612691421233152
