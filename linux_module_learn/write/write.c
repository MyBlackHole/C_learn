#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/syscalls.h>
#include "linux/err.h"
// #include <linux/file.h>

static struct file *log_fsbackup_fp = NULL;

__attribute__((optimize("O0"))) static int __init write_init(void)
{
	int64_t write_size = 0;
	char sys_hook_event_buf[1024];
	loff_t pos = 0;
	int i, j;
	// mm_segment_t old_fs;

	// // 6.x 不需要 get_fs
	// old_fs = get_fs();
	// set_fs(KERNEL_DS);
	//
	printk("write_init!\n");

	// 缺少目录时会: [ 7175.945832] error: line:29, error code: -2
	log_fsbackup_fp = filp_open(
		"/run/media/black/Data/Documents/c/linux_module_learn/write/write.img",
		O_RDWR | O_CREAT, 0666);

	if (IS_ERR(log_fsbackup_fp)) {
		printk("error: line:%d, error code: %ld\n", __LINE__,
		       PTR_ERR(log_fsbackup_fp));
		return -1;
	}

	for (j = 0; j < 1024; j++) {
		sys_hook_event_buf[j] = 'a';
	}

	// 写入 3G 数据
	for (i = 0; i < 3 * 1024; i++) {
		// 这里应该有个循环取保写入 1024 字节
		/* sys_write only can write MAX_RW_COUNT aka 2G-4K bytes at most */
		write_size = kernel_write(log_fsbackup_fp,
					  sys_hook_event_buf + write_size, 1024,
					  &pos);

		// if (write_size == -EINTR || write_size == -EAGAIN)
		//     continue;

		if (write_size <= 0 && write_size != -ERESTARTSYS &&
		    write_size != -EAGAIN && write_size != -EINTR)

		{
			printk("error: line:%d, error code: %lld\n", __LINE__,
			       write_size);
			break;
		}
		// write_size = vfs_write(log_fsbackup_fp, sys_hook_event_buf, 1024,
		// &pos);
		if (write_size != 1024) {
			printk("error: line:%d, error code: %ld\n", __LINE__,
			       PTR_ERR(log_fsbackup_fp));
			break;
		}

		printk("info: line:%d, log_fsbackup_fp.f_pos: %lld.\n",
		       __LINE__, log_fsbackup_fp->f_pos);

		printk("info: line:%d, ssleep.\n", __LINE__);
		ssleep(10);
	}

	if (filp_close(log_fsbackup_fp, NULL) != 0) {
		printk("error: line:%d, close failure.\n", __LINE__);
	}

	// set_fs(old_fs);
	return 0;
}
static void __exit write_exit(void)
{
	printk("write_exit!\n");
}
module_init(write_init);
module_exit(write_exit);
MODULE_LICENSE("GPL");
