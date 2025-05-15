#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/ptrace.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

static struct kprobe kp;
int last_pid = 0;

/* Handler for the probed function (__x64_sys_open) */
static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
	if (current->pid == last_pid) {
		return 0;
	}
	pr_info("[+] Hooked __x64_sys_open! PID: %d, name: %s", current->pid,
		current->comm);
	last_pid = current->pid;
	return 0;
}

static int __init hook_init(void)
{
	kp.symbol_name = "__x64_sys_open";
	kp.pre_handler = handler_pre;

	if (register_kprobe(&kp)) {
		pr_err("[-] Failed to register kprobe\n");
		return -1;
	}

	pr_info("[+] __x64_sys_open hooked successfully at address: %p\n",
		kp.addr);
	return 0;
}

static void __exit hook_exit(void)
{
	unregister_kprobe(&kp);
	pr_info("[+] __x64_sys_open unhooked successfully\n");
}

module_init(hook_init);
module_exit(hook_exit);
