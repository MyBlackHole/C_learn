#include "asm/pgtable.h"
#include "linux/moduleparam.h"
#include "linux/sched.h"
#include "linux/mm.h"

static int pid;
static unsigned long va;

module_param(pid, int, 0644); // process pid
module_param(va, ulong, 0644); // process virtuall address

static void user_test(void)
{
	unsigned long pa = 0; // physics address
	struct task_struct *pcb = NULL; // process task struct
	struct pid *p = NULL;

	pgd_t *pgd = NULL;
	p4d_t *p4d = NULL;
	pud_t *pud = NULL;
	pmd_t *pmd = NULL;
	pte_t *pte = NULL;

	p = find_vpid(pid);
	if (p == NULL)
		return;
	pcb = pid_task(p, PIDTYPE_PID);
	if (pcb == NULL)
		return;
	if (!find_vma(pcb->mm, va)) {
		printk("virtual address 0x%lx is not available\n", va);
		return;
	}

	pgd = pgd_offset(pcb->mm, va);
	printk("pgd = 0x%p\n", pgd);
	printk("pgd_val = 0x%lx,   pgd_index = %lu\n", pgd_val(*pgd),
	       pgd_index(va));
	if (pgd_none(*pgd)) {
		printk("not mapped in pgd\n");
		return;
	}

	p4d = p4d_offset(pgd, va);
	printk("p4d = 0x%p\n", p4d);
	printk("p4d_val = 0x%lx,   p4d_index = %lu\n", p4d_val(*p4d),
	       p4d_index(va));
	if (p4d_none(*p4d)) {
		printk("not mapped in p4d\n");
		return;
	}

	pud = pud_offset(p4d, va);
	printk("pud = 0x%p\n", pud);
	printk("pud_val = 0x%lx,   pud_index = %lu\n", pud_val(*pud),
	       pud_index(va));
	if (pud_none(*pud)) {
		printk("not mapped in pud\n");
		return;
	}

	pmd = pmd_offset(pud, va);
	printk("pmd = 0x%p\n", pmd);
	printk("pmd_val = 0x%lx,   pmd_index = %lu\n", pmd_val(*pmd),
	       pmd_index(va));
	if (pmd_none(*pmd)) {
		printk("not mapped in pmd\n");
		return;
	}

	pte = pte_offset_kernel(pmd, va);
	printk("pte = 0x%p\n", pte);
	printk("pte_val = 0x%lx,   pte_index = %lu\n", pte_val(*pte),
	       pte_index(va));
	if (pte_none(*pte)) {
		printk("not mapped in pte\n");
		return;
	}
	if (!pte_present(*pte)) {
		printk("pte not in RAM\n");
		return;
	}

	pa = (pte_val(*pte) & PAGE_MASK);
	printk("virtual address 0x%lx --> physics address 0x%lx\n", va, pa);
}
