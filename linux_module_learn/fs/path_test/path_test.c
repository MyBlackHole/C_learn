#include "linux/printk.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/namei.h>
#include <linux/version.h>
#include <linux/file.h>
#include <linux/fs.h>

#define FILE_TEST "./home/black/bashrc"

#define TASK_PATH_MAX_LENGTH 512

static char *pathname = FILE_TEST;

module_param(pathname, charp, 0644);

char *get_file_info(unsigned int fd, char *filename_buf, const int buflen,
		    int64_t *offset)
{
	char *pathname = NULL;
	struct inode *inode = NULL;
	struct fd f;

	f = fdget(fd);
	*offset = 0;
	if (f.file) {
		inode = file_inode(f.file);
		if (f.file->f_flags & O_APPEND) {
			*offset = i_size_read(inode);
		} else {
			*offset = f.file->f_pos;
		}
		pathname = d_path(&f.file->f_path, filename_buf, buflen);
		if (IS_ERR(pathname)) {
			filename_buf[0] = 0x00;
		} else {
			memcpy(filename_buf, pathname, strlen(pathname));
			filename_buf[strlen(pathname)] = 0x00;
		}
		fdput(f);
	} else {
		filename_buf[0] = 0x00;
	}

	return filename_buf;
}

char *get_file_real_path(int dfd, const char *filename, char *filename_buf,
			 const int buflen)
{
	int ret = 0;
	struct path path;
	const char *pathname = NULL;

	ret = kern_path(filename, LOOKUP_FOLLOW, &path);
	if (ret) {
		pr_err("%s: user_path_at failed, ret = %d\n", __func__, ret);
		goto err;
	}
	pathname = d_path(&path, filename_buf, buflen);
	if (IS_ERR(pathname)) {
		ret = PTR_ERR(pathname);
		pr_err("%s: real path is %d\n", __func__, ret);
		goto free_path;
	} else {
		memcpy(filename_buf, pathname, strlen(pathname));
		filename_buf[strlen(pathname)] = 0x00;
	}

	path_put(&path);
	return filename_buf;
free_path:
	path_put(&path);
err:
	filename_buf[0] = 0x00;
	return filename_buf;
}

static int __init path_init(void)
{
	char buf[TASK_PATH_MAX_LENGTH] = { 0 };
	int ret = -1;

	get_file_real_path(AT_FDCWD, pathname, buf, TASK_PATH_MAX_LENGTH - 1);
	pr_info("%s: real path is %s\n", __func__, buf);

	return ret;
}

static void __exit path_exit(void)
{
	printk(KERN_INFO "%s: exit called\n", __func__);
}

module_init(path_init);
module_exit(path_exit);

MODULE_AUTHOR("blackhole <1358244533@qq.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("nfs hook module test!");
