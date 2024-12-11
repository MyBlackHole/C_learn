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

int __init file_init(void)
{
	int retry = 10;
	int err = 0;
	unsigned char buf1[12] = "hello world.";
	char *file = "/tmp/file_test";

	loff_t pos;

	pr_err("------ file close test ------\n");
	fp = filp_open(file, O_RDWR | O_CREAT, 0644);
	if (IS_ERR(fp)) {
		pr_err("open file error %ld\n", PTR_ERR(fp));
		fp = NULL;
		return -1;
	} else {
		pr_info("open file success\n");
	}

	pr_info("fp->f_op: %p, (unsigned long)fp->f_op: 0x%lx\n", fp->f_op,
		(unsigned long)fp->f_op);

	pos = fp->f_pos;
	err = kernel_write(fp, buf1, sizeof(buf1), &pos);
	if (err < 0) {
		pr_err("write file error %d\n", err);
	}
	fp->f_pos = pos;

	while (retry--) {
		err = filp_close(fp, NULL);
		if (err != 0) {
			fp = NULL;
			pr_err("close file error %d\n", err);
			break;
		} else {
			pr_info("close file success\n");
		}
		pr_info("fp->f_op: %p, (unsigned long)fp->f_op: 0x%lx, retry: %d\n",
			fp->f_op, (unsigned long)fp->f_op, retry);
		ssleep(2);

		fp = filp_open(file, O_RDWR | O_CREAT, 0644);
		if (IS_ERR(fp)) {
			fp = NULL;
			pr_err("open file error %ld\n", PTR_ERR(fp));
			return -1;
		} else {
			pr_info("open file success\n");
		}
	}

	return 0;
}

void __exit file_exit(void)
{
	if (!IS_ERR(fp)) {
		pr_info("fp->f_op: %p, (unsigned long)fp->f_op: 0x%lx\n",
			fp->f_op, (unsigned long)fp->f_op);
		filp_close(fp, NULL);
		pr_info("close file success\n");
	}
	pr_info("------ file test exit ------\n");
}

module_init(file_init);
module_exit(file_exit);

MODULE_LICENSE("GPL");
