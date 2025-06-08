#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/version.h>
#include <linux/printk.h>

static int mem = 1;

#define MB (1024 * 1024)

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0)
#define MAX_ORDER 12
#endif

static int __init my_init(void)
{
	char *kbuf;
	unsigned long order;
	unsigned long size;
	char *vm_buff;
	/*char *p_c1 = 0x00000000ca6b6ded;*/
	/*char *p_c2 = 0x000000008e5d0e62;*/

	/*struct file *fp = (struct file *)p_c1;*/

	/*if (IS_ERR(fp)) {*/
	/*	pr_info("... p1 is not a valid file pointer\n");*/
	/*} else {*/
	/*	pr_info("... p1 is a valid file pointer\n");*/
	/*	pr_info("... p1->f_count = %ld\n", fp->f_count.counter);*/
	/*	pr_info("... p1->f_op->owner = %p\n", fp->f_op);*/
	/*}*/

	/*pr_info("check p1\n");*/
	/*if (virt_addr_valid(p_c1))*/
	/*	pr_info("... p1 is valid\n");*/
	/*else*/
	/*	pr_info("... p1 is invalid\n");*/
	/**/
	/*pr_info("check p2\n");*/
	/*if (virt_addr_valid(p_c2))*/
	/*	pr_info("... p2 is valid\n");*/
	/*else*/
	/*	pr_info("... p2 is invalid\n");*/

	/* try kmalloc */
	pr_info("kmalloc start ----------------\n");
	for (size = PAGE_SIZE, order = 0; order < mem; order++, size *= 2) {
		kbuf = kmalloc((size_t)size, GFP_ATOMIC);
		if (!kbuf) {
			pr_err("... kmalloc failed\n");
			break;
		}
		if (virt_addr_valid(kbuf))
			pr_info("... kbuf %p is valid\n", kbuf);
		else
			pr_info("... kbuf %p is invalid\n", kbuf);
		pr_info("kfree start\n");
		kfree(kbuf);
		pr_info("kfree end\n");
		if (virt_addr_valid(kbuf))
			pr_info("... kbuf %p is valid\n", kbuf);
		else
			pr_info("... kbuf %p is invalid\n", kbuf);
		memset(kbuf + size, 0, 3);
	}
	pr_info("kmalloc end ----------------\n");

	/* try vmalloc */
	pr_info("vmalloc start ----------------\n");
	for (size = 1 * MB; size <= mem * MB; size += 1 * MB) {
		vm_buff = vmalloc(size);
		if (!vm_buff) {
			pr_err("... vmalloc failed\n");
			break;
		}
		/*memset(vm_buff, 0, size);*/
		if (virt_addr_valid(vm_buff))
			pr_info("... vm_buff %p is valid\n", vm_buff);
		else
			pr_info("... vm_buff %p is invalid\n", vm_buff);
		pr_info("vfree start\n");
		vfree(vm_buff);
		pr_info("vfree end\n");

		if (virt_addr_valid(vm_buff))
			pr_info("... vm_buff %p is valid\n", vm_buff);
		else
			pr_info("... vm_buff %p is invalid\n", vm_buff);
		memset(vm_buff, 0, size + 1);
	}
	pr_info("vmalloc end ----------------\n");

	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Module exit\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL v2");
