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

int __init hello_init(void)
{
	/*int retry = 10;*/
	int err = 0;
	unsigned char buf1[12] = "hello world.";

	struct file f;
	struct file *fp = &f;
	loff_t pos;

	printk("hello enter\n");
	/*fp = filp_open("/tmp/file_test", O_RDWR | O_CREAT, 0644);*/
	/*if (IS_ERR(fp)) {*/
	/*	printk("create file error\n");*/
	/*	return -1;*/
	/*}*/
	/*fp = (struct file *)kmalloc(sizeof(struct file), GFP_KERNEL);*/

	printk("%ld, %ld, %ld, %ld\n", offsetof(struct file, f_op),
	       offsetof(struct file, f_flags), offsetof(struct file, f_pos),
	       offsetof(struct file_operations, flush));

	pos = fp->f_pos;
	err = kernel_write(fp, buf1, sizeof(buf1), &pos);
	if (err < 0) {
		printk("write file error %d\n", err);
	}
	fp->f_pos = pos;

	filp_close(fp, NULL);
	/*while (retry--) {*/
	/*	if (fp->f_op) {*/
	/*		printk("f_op is not null");*/
	/*		if (fp->f_op->flush) {*/
	/*			printk("flush is not null");*/
	/*		} else {*/
	/*			printk("flush is null");*/
	/*		}*/
	/*	} else {*/
	/*		printk("f_op is null");*/
	/*	}*/
	/*	ssleep(20);*/
	/*	filp_close(fp, NULL);*/
	/*}*/

	return 0;
}

void __exit hello_exit(void)
{
	printk("hello exit\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
