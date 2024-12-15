#include "linux/printk.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/version.h>

#define KB (1024)

static int __init my_init(void)
{
	unsigned long *ptr = 0xffff88822df04c00;

	pr_info("Module init\n");
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
// [  742.989280] hw_breakpoint hello world!
// [  742.990747] ptr = 00000000bf8945d2
// [  742.992019] ptr = 0xffff88822df04c00
// [  742.993435] physical address = 0x22df04c00
// [  742.995575] physical address = 0x22df04c00
// [  742.998921] register_wide_hw_breakpoint success
// # insmod vir_hw_mm.ko
// [  881.658084] Module init
// [  881.659677] ptr is "3D
// [  881.661206] CPU: 3 PID: 1637 Comm: insmod Tainted: G        W  O      4.19.315 #13
// [  881.662153] Hardware name: QEMU Standard PC (i440FX + PIIX, 1996), BIOS Arch Linux 1.16.3-1-1 04/01/2014
// [  881.662153] Call Trace:
// [  881.662153]  <#DB>
// [  881.662153]  dump_stack+0x50/0x63
// [  881.662153]  sample_hbp_handler+0x17/0x1d [hw_breakpoint]
// [  881.662153]  __perf_event_overflow+0x80/0x1b0
// [  881.662153]  perf_bp_event+0x99/0xa0
// [  881.662153]  hw_breakpoint_exceptions_notify+0xdd/0x110
// [  881.662153]  notify_die+0x71/0xa0
// [  881.662153]  do_debug+0xcb/0x1e0
// [  881.662153]  debug+0x28/0x50
// [  881.662153] RIP: 0010:my_init+0x38/0x1000 [vir_hw_mm]
// [  881.662153] Code: 82 88 ff ff e8 ba c2 d1 e1 48 89 de 48 c7 c7 0f 60 00 a0 e8 ab c2 d1 e1 b8 99 99 99 99 48 89 de 48 c7 c7 0f 60 00 a0 48 89 03 <e8> 94 c2 d1 e1 48 8b 33 48 c7 0
// [  881.662153] RSP: 0018:ffffc90000d63de0 EFLAGS: 00000246
// [  881.662153] RAX: 0000000099999999 RBX: ffff88822df04c00 RCX: ffffffff81927bc0
// [  881.662153] RDX: 0000000000000000 RSI: ffff88822df04c00 RDI: ffffffffa000600f
// [  881.662153] RBP: 0000000000000000 R08: 000000000000022e R09: 0000000000000000
// [  881.662153] R10: 0000000000000000 R11: 0000000000000010 R12: 00005637c80c92a0
// [  881.662153] R13: 0000000000000003 R14: 0000000000000000 R15: 0000000000000000
// [  881.662153]  ? netconsole_netdev_event+0x150/0x150
// [  881.662153]  </#DB>
// [  881.662153]  ? 0xffffffffa000a000
// [  881.662153]  do_one_initcall+0x3f/0x1c0
// [  881.662153]  ? _cond_resched+0x11/0x40
// [  881.662153]  ? kmem_cache_alloc_trace+0x35/0x160
// [  881.662153]  do_init_module+0x47/0x250
// [  881.662153]  __do_sys_finit_module+0xb7/0xd0
// [  881.662153]  do_syscall_64+0x43/0x100
// [  881.662153]  entry_SYSCALL_64_after_hwframe+0x5c/0xc1
// [  881.662153] RIP: 0033:0x7f5b87090a49
// [  881.662153] Code: ff c3 66 2e 0f 1f 84 00 00 00 00 00 0f 1f 44 00 00 48 89 f8 48 89 f7 48 89 d6 48 89 ca 4d 89 c2 4d 89 c8 4c 8b 4c 24 08 0f 05 <48> 3d 01 f0 ff ff 73 01 c3 48 8
// [  881.662153] RSP: 002b:00007ffd1731e918 EFLAGS: 00000246 ORIG_RAX: 0000000000000139
// [  881.662153] RAX: ffffffffffffffda RBX: 00005637c80c92a0 RCX: 00007f5b87090a49
// [  881.662153] RDX: 0000000000000000 RSI: 00005637c80c92a0 RDI: 0000000000000003
// [  881.662153] RBP: 0000000000000003 R08: 0000000000000001 R09: 0000000000480000
// [  881.662153] R10: 0000000000000020 R11: 0000000000000246 R12: 00007ffd1731ef58
// [  881.662153] R13: 00007ffd1731eb20 R14: 00007f5b871b9000 R15: 00005637c731e358
// [  881.733602] ptr is
// [  881.734166] New Data: 0x99999999
