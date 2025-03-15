#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

// 定义虚拟文件内容
static const char *hello_str = "Hello, FUSE!\n";
static const char *hello_path = "/hello.txt";

// 实现 getattr：获取文件/目录属性
static int simple_getattr(const char *path, struct stat *stbuf)
{
	int res = 0;
	memset(stbuf, 0, sizeof(struct stat));

	if (strcmp(path, "/") == 0) { // 根目录属性
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	} else if (strcmp(path, hello_path) == 0) { // hello.txt 文件属性
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(hello_str);
	} else { // 文件不存在
		res = -ENOENT;
	}
	return res;
}

// 实现 readdir：读取目录内容
static int simple_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			  off_t offset, struct fuse_file_info *fi)
{
	(void)offset;
	(void)fi;

	if (strcmp(path, "/") != 0)
		return -ENOENT;

	filler(buf, ".", NULL, 0); // 当前目录
	filler(buf, "..", NULL, 0); // 上级目录
	filler(buf, "hello.txt", NULL, 0); // 虚拟文件
	return 0;
}

// 实现 open：打开文件
static int simple_open(const char *path, struct fuse_file_info *fi)
{
	if (strcmp(path, hello_path) != 0)
		return -ENOENT;
	return 0;
}

// 实现 read：读取文件内容
static int simple_read(const char *path, char *buf, size_t size, off_t offset,
		       struct fuse_file_info *fi)
{
	if (strcmp(path, hello_path) != 0)
		return -ENOENT;

	size_t len = strlen(hello_str);
	if (offset >= len)
		return 0;

	if (offset + size > len)
		size = len - offset;

	memcpy(buf, hello_str + offset, size);
	return size;
}

// 定义 FUSE 操作函数结构体
static struct fuse_operations simple_ops = {
	.getattr = simple_getattr,
	.readdir = simple_readdir,
	.open = simple_open,
	.read = simple_read,
};

int demo_fuse_main(int argc, char *argv[])
{
	return fuse_main(argc, argv, &simple_ops, NULL);
}
