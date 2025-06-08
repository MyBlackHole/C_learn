#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/dcache.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <asm/fcntl.h>
#include <asm/processor.h>
#include <asm/uaccess.h>

static struct file *fp = NULL;

int __init my_init(void)
{
	int err = 0;
	unsigned char buf1[12] = "hello world.";

	loff_t pos;

	pr_info("open demo enter\n");
	fp = filp_open("/tmp/file_test", O_RDWR | O_CREAT, 0644);
	if (IS_ERR(fp)) {
		printk("create file error\n");
		return -1;
	}
	pr_info("&fp->f_op is %lx\n", (unsigned long)&fp->f_op);
	pr_info("fp->f_op is %lx\n", (unsigned long)fp->f_op);
	pr_info("fp->f_op phy addr is 0x%lx\n",
		(unsigned long)virt_to_phys((void *)(unsigned long)&fp->f_op));
	pr_info("fp->f_count is %ld\n", fp->f_count.counter);
	/*pr_info("%ld, %ld, %ld, %ld\n", offsetof(struct file, f_op),*/
	/*	offsetof(struct file, f_flags), offsetof(struct file, f_pos),*/
	/*	offsetof(struct file_operations, flush));*/

	pos = fp->f_pos;
	err = kernel_write(fp, buf1, sizeof(buf1), &pos);
	if (err < 0) {
		pr_err("write file error %d\n", err);
	}
	fp->f_pos = pos;

	return 0;
}

void __exit my_exit(void)
{
	pr_info("open demo exit\n");
	pr_info("fp->f_op is %lx\n", (unsigned long)&fp->f_op);
	pr_info("fp->f_count is %ld\n", fp->f_count.counter);
	pr_info("fp->f_op phy addr is 0x%lx\n",
		(unsigned long)virt_to_phys((void *)(unsigned long)&fp->f_op));
	filp_close(fp, NULL);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
