#include "path.h"

#include <linux/version.h>
#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include "linux/file.h"
#include "linux/namei.h"

char *get_file_real_path(int dfd, const char __user *filename,
			 char *filename_buf, const int buflen)
{
	int ret = 0;
	struct path path;
	const char *pathname = NULL;

	ret = user_path_at(dfd, filename, LOOKUP_FOLLOW, &path);
	if (ret) {
		goto err;
	}
	pathname = d_path(&path, filename_buf, buflen);
	if (IS_ERR(pathname)) {
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
