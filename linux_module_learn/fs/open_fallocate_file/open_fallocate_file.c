#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kernel.h>

static struct file *fp = NULL;

int __init file_init(void)
{
	int err = 0;
	char *file = "/tmp/file_test";

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

	if (!IS_ERR(fp)) {
		/*FALLOC_FL_ALLOCATE_RANGE = 0*/
		err = vfs_fallocate(fp, 0, 0, 16 * 1024 * 1024);
		if (err != 0) {
			pr_err("fallocate file error %d\n", err);
			fp = NULL;
			return -1;
		} else {
			pr_info("fallocate file success\n");
		}
	}

	return 0;
}

void __exit file_exit(void)
{
	int err = 0;
	if (!IS_ERR(fp)) {
		err = filp_close(fp, NULL);
		if (err != 0) {
			fp = NULL;
			pr_err("close file error %d\n", err);
		} else {
			pr_info("close file success\n");
		}
	}
	pr_info("------ file test exit ------\n");
}

module_init(file_init);
module_exit(file_exit);

MODULE_LICENSE("GPL");

// output:
//
// # insmod open_fallocate_file.ko
// [ 1231.609523] ------ file close test ------
// [ 1231.611200] open file success
// [ 1231.612434] fp->f_op: 00000000062542b0, (unsigned long)fp->f_op: 0xffffffff82215900
// [ 1231.618500] fallocate file success
// # ls -alh /tmp/file_test
// -rw-r--r--    1 root     root       16.0M Jan 24 02:18 /tmp/file_test
// # rmmod open_fallocate_file.ko
// [ 1238.298850] close file success
// [ 1238.300421] ------ file test exit ------
