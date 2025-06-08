// SPDX-License-Identifier: (GPL-2.0 OR MIT)
/**
 * Test syscall table hijacking on x86-64. This module will replace the `read`
 * syscall with a simple wrapper which logs every invocation of `read` using
 * printk().
 *
 * Tested on Linux x86-64 v5.10, v5.18.
 *
 * Usage:
 *
 *     sudo cat /proc/kallsyms | grep sys_call_table # grab address
 *     sudo insmod syscall_hijack.ko sys_call_table_addr=0x<address_here>
 */

#include <linux/init.h> // module_{init,exit}()
#include <linux/module.h> // THIS_MODULE, MODULE_VERSION, ...
#include <linux/kernel.h> // printk(), pr_*()
#include <asm/special_insns.h> // {read,write}_cr0()
#include <asm/processor-flags.h> // X86_CR0_WP
#include <asm/unistd.h> // __NR_*

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

typedef long (*sys_call_ptr_t)(const struct pt_regs *);

static sys_call_ptr_t *real_sys_call_table;
static sys_call_ptr_t original_read;

static unsigned long sys_call_table_addr;
module_param(sys_call_table_addr, ulong, 0);
MODULE_PARM_DESC(sys_call_table_addr, "Address of sys_call_table");

// Since Linux v5.3 [native_]write_cr0 won't change "sensitive" CR0 bits, need
// to re-implement this ourselves.
static void write_cr0_unsafe(unsigned long val)
{
	asm volatile("mov %0,%%cr0" : "+r"(val) : : "memory");
}

static long myread(const struct pt_regs *regs)
{
	pr_info("read(%ld, 0x%lx, 0x%lx)\n", regs->di, regs->si, regs->dx);
	return original_read(regs);
}

static int __init modinit(void)
{
	unsigned long old_cr0;

	real_sys_call_table = (typeof(real_sys_call_table))sys_call_table_addr;

	pr_info("init\n");

	// Temporarily disable CR0 WP to be able to write to read-only pages
	old_cr0 = read_cr0();
	write_cr0_unsafe(old_cr0 & ~(X86_CR0_WP));

	// Overwrite syscall and save original to be restored later
	original_read = real_sys_call_table[__NR_read];
	real_sys_call_table[__NR_read] = myread;

	// Restore CR0 WP
	write_cr0_unsafe(old_cr0);
	pr_info("init done\n");

	return 0;
}

static void __exit modexit(void)
{
	unsigned long old_cr0;

	pr_info("exit\n");

	old_cr0 = read_cr0();
	write_cr0_unsafe(old_cr0 & ~(X86_CR0_WP));

	// Restore original syscall
	real_sys_call_table[__NR_read] = original_read;

	write_cr0_unsafe(old_cr0);

	pr_info("goodbye\n");
}

module_init(modinit);
module_exit(modexit);
MODULE_VERSION("0.1");
MODULE_DESCRIPTION("Test syscall table hijacking on x86-64.");
MODULE_AUTHOR("Marco Bonelli");
MODULE_LICENSE("Dual MIT/GPL");
