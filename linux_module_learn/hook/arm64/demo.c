#include <linux/init.h>
#include <linux/mm.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kallsyms.h>
#include <linux/syscalls.h>
#include <asm/unistd.h>
#include <asm/ptrace.h>
#include <asm/pgtable.h>
#include <asm/tlbflush.h>

static pte_t *ptep;
static struct mm_struct *mm;

static unsigned long *__sys_call_table;
static unsigned long mkdir_sys_call_addr;

typedef long (*syscall_fn_t)(const struct pt_regs *regs);

#ifndef __NR_mkdirat
#define __NR_mkdirat 34
#endif

//用于保存原始的 mkdir 系统调用
static syscall_fn_t orig_mkdir;

asmlinkage long mkdir_hook(const struct pt_regs *regs)
{
	printk("hook mkdir sys_call\n");

	//return orig_mkdir(regs);
	return 0;
}

static void set_pte_write(void)
{
	pte_t pte;

	pte = READ_ONCE(*ptep);

	//清除pte的可读属性位
	//设置pte的可写属性位
	pte = pte_mkwrite(pte);

	//把pte页表项写入硬件页表钟
	set_pte_at(mm, mkdir_sys_call_addr, ptep, pte);

	//页表更新 和 TLB 刷新之间保持正确的映射关系
	//为了保持一致性，必须确保页表的更新和 TLB 的刷新是同步的
	__flush_tlb_kernel_pgtable(mkdir_sys_call_addr);
}

static void set_pte_rdonly(void)
{
	pte_t pte;

	pte = READ_ONCE(*ptep);

	//清除pte的可写属性位
	//设置pte的可读属性位
	pte = pte_wrprotect(pte);

	set_pte_at(mm, mkdir_sys_call_addr, ptep, pte);

	__flush_tlb_kernel_pgtable(mkdir_sys_call_addr);
}

//内核模块初始化函数
static int __init lkm_init(void)
{
	pgd_t *pgdp;
	pud_t *pudp;
	pmd_t *pmdp;

	/* can be directly found in kernel memory */
	mm = (struct mm_struct *)kallsyms_lookup_name("init_mm");
	if (mm == NULL)
		return -1;

	__sys_call_table =
		(unsigned long *)kallsyms_lookup_name("sys_call_table");
	if (!__sys_call_table)
		return -1;

	mkdir_sys_call_addr = (unsigned long)(__sys_call_table + __NR_mkdirat);

	pgdp = pgd_offset(mm, mkdir_sys_call_addr);
	if (pgd_none(READ_ONCE(*pgdp))) {
		printk(KERN_INFO "failed pgdp");
		return 0;
	}

	pudp = pud_offset(pgdp, mkdir_sys_call_addr);
	if (pud_none(READ_ONCE(*pudp))) {
		printk(KERN_INFO "failed pudp");
		return 0;
	}

	pmdp = pmd_offset(pudp, mkdir_sys_call_addr);
	if (pmd_none(READ_ONCE(*pmdp))) {
		printk(KERN_INFO "failed pmdp");
		return 0;
	}

	ptep = pte_offset_kernel(pmdp, mkdir_sys_call_addr);
	if (!pte_valid(READ_ONCE(*ptep))) {
		printk(KERN_INFO "failed pte");
		return 0;
	}

	//保存原始的系统调用：mkdir
	orig_mkdir = (syscall_fn_t)__sys_call_table[__NR_mkdirat];

	set_pte_write();
	__sys_call_table[__NR_mkdirat] = (unsigned long)mkdir_hook;
	set_pte_rdonly();

	printk("lkm_init\n");

	return 0;
}

//内核模块退出函数
static void __exit lkm_exit(void)
{
	set_pte_write();
	__sys_call_table[__NR_mkdirat] = (unsigned long)orig_mkdir;
	set_pte_rdonly();

	printk("lkm_exit\n");
}

module_init(lkm_init);
module_exit(lkm_exit);

MODULE_LICENSE("GPL");
