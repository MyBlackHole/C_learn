//kernel module to hook read system call with the help of kprobes / kallsyms_lookup_name

#include <linux/kprobes.h>
#include <asm/special_insns.h>
#include <asm/processor-flags.h>

MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");

void cr0_write(unsigned long val);
int new_read(struct pt_regs *regs);
typedef int (*sysfun_t)(struct pt_regs *);
typedef void *(*kallsyms_t)(const char *);
sysfun_t old_read;
extern unsigned long __force_order;

void cr0_write(unsigned long val)
{
	asm volatile("mov %0,%%cr0" : "+r"(val) : : "memory");
}

static inline unsigned long unprotect_memory(void)
{
	unsigned long cr0;
	unsigned long newcr0;
	cr0 = native_read_cr0();
	newcr0 = cr0 & ~(X86_CR0_WP); // and not ==> remove write protection
	cr0_write(newcr0);
	if (cr0 != native_read_cr0())
		pr_info("[+] Write protection disabled\n");
	return cr0;
}

static inline void protect_memory(unsigned long cr0)
{
	cr0_write(cr0);
}

int new_read(struct pt_regs *regs)
{
	pr_info("[+] Hooked read() syscall\n");
	return old_read(regs);
}

static int __init hook_init(void)
{
	struct kprobe probe = {
		.symbol_name = "kallsyms_lookup_name",
	};
	if (register_kprobe(&probe)) {
		pr_err("[-] Failed to get kallsyms_lookup_name() address.\n");
		return 0;
	}

	// function pointer type of kallsyms_lookup_name
	kallsyms_t lookup_name;
	lookup_name = (kallsyms_t)(probe.addr);
	uint64_t *syscall_table = 0;
	syscall_table = lookup_name("sys_call_table");

	if (!syscall_table) {
		pr_err("[-] Failed to get sys_call_table address.\n");
		unregister_kprobe(&probe);
		return 0;
	}

	pr_info("[+] kallsyms_lookup_name(): %p, sys_call_table: %p\n",
		probe.addr, syscall_table);

	uint64_t old_cr0 = unprotect_memory();
	old_read = (sysfun_t)syscall_table[__NR_read];

	pr_info("[+] old_read() address: %p\n", (void *)old_read);

	syscall_table[__NR_read] = (uint64_t)new_read;
	protect_memory(old_cr0);

	// Vérifications supplémentaires
	pr_info("[+] new_read() address: %p\n",
		(void *)syscall_table[__NR_read]);

	// Vérifier que l'adresse a bien été changée
	if (syscall_table[__NR_read] != (uint64_t)new_read) {
		pr_err("[-] Hook installation failed: addresses don't match\n");
		return 0;
	}

	// Vérifier que l'ancienne et la nouvelle adresse sont différentes
	if (syscall_table[__NR_read] == (uint64_t)old_read) {
		pr_err("[-] Hook installation failed: address unchanged\n");
		return 0;
	}

	pr_info("[+] read() syscall hooked successfully\n");
	//    unregister_kprobe(&probe);
	return 0;
}

static void __exit hook_exit(void)
{
	return;
}

module_init(hook_init);
module_exit(hook_exit);
