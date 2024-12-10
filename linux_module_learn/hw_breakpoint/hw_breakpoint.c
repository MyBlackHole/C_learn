#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hw_breakpoint.h>
#include "linux/slab.h"

static char *ptr;

struct perf_event *__percpu *sample_hbp;

static void sample_hbp_handler(struct perf_event *bp,
			       struct perf_sample_data *data,
			       struct pt_regs *regs)
{
	dump_stack();
}

static int __init hb_hello(void)
{
	struct perf_event_attr attr;
	size_t size = 1024;
	pr_info("hw_breakpoint hello world!\n");

	ptr = kmalloc(size, GFP_KERNEL);
	if (!ptr) {
		pr_err("kmalloc failed\n");
		return -1;
	}
	pr_info("ptr = %p\n", ptr);
	pr_info("ptr = 0x%lx\n", (unsigned long)ptr);
	pr_info("physical address = 0x%lx\n", (unsigned long)virt_to_phys(ptr));
	pr_info("physical address = 0x%lx\n", (unsigned long)ptr - PAGE_OFFSET);
	ptr[0] = 0x11;
	ptr[1] = 0x22;
	ptr[2] = 0x33;
	ptr[3] = 0x44;
	hw_breakpoint_init(&attr);
	// attr.bp_addr = (unsigned long)virt_to_phys(ptr); /* 待监视的地址 */
	attr.bp_addr = (unsigned long)ptr; /* 待监视的地址 */
	attr.bp_len = HW_BREAKPOINT_LEN_4;
	attr.bp_type = HW_BREAKPOINT_W; /* 待监视的访问类型 */

	sample_hbp =
		register_wide_hw_breakpoint(&attr, sample_hbp_handler, NULL);
	if (IS_ERR(sample_hbp)) {
		pr_err("register_wide_hw_breakpoint failed\n");
		return -1;
	}
	pr_info("register_wide_hw_breakpoint success\n");

	/*if (set_addr_ro((unsigned long)ptr)) {*/
	/*	pr_err("set_addr_ro failed\n");*/
	/*	return;*/
	/*}*/

	/*ptr[size] = 'a';*/
	/*pr_info("ptr[size] = %c\n", ptr[size]);*/
	return 0;
}

static void __exit hb_exit(void)
{
	pr_info("kasan good bye!\n");
	/*if (set_addr_rw((unsigned long)ptr)) {*/
	/*	pr_err("set_addr_rw failed\n");*/
	/*}*/
	ptr[1] = 'b';
	if (sample_hbp)
		unregister_wide_hw_breakpoint(sample_hbp);
	kfree(ptr);
}

module_init(hb_hello);
module_exit(hb_exit);

MODULE_LICENSE("GPL");

// output:
//
// # insmod hw_breakpoint.ko
// [  300.166282] hw_breakpoint hello world!
// [  300.168295] ptr = 0000000077b3e6e9
// [  300.170003] ptr = 0xffff8881e5ca5608
// [  300.172099] physical address = 0x1e5ca5608
// [  300.174300] physical address = 0x1e5ca5608
// [  300.177127] register_wide_hw_breakpoint success
