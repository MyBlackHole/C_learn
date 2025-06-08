#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <linux/kallsyms.h>
#include <linux/version.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/limits.h>

#include "../imp/hook_api.h"
#include "../imp/arch.h"
#include "../utils/path.h"

#define USER_PATH_MAX_LEN PATH_MAX + 12

static atomic64_t reference_count;

#define HOOK_INIT                                  \
	do {                                       \
		atomic64_set(&reference_count, 0); \
	} while (0)

#define HOOK_BEGIN                                         \
	{                                                  \
		do {                                       \
			atomic64_add(1, &reference_count); \
		} while (0)

#define HOOK_COMPLETED                             \
	do {                                       \
		atomic64_sub(1, &reference_count); \
	} while (0);                               \
	}

#define HOOK_SAFTY_EXIT (0 == atomic64_sub_return(0, &reference_count))

#define HOOK_COUNT (atomic64_sub_return(0, &reference_count))

typedef asmlinkage long (*func_ptr_t)(const struct pt_regs *);
// hook api

// sys_call_funcptr_t original_access;

// 内部 api 调用, 不进行 hook 使用
#if defined(__NR_faccessat)
func_ptr_t original_faccessat;
#endif // __NR_faccessat
#if defined(__NR_chmod)
func_ptr_t original_chmod;
#endif // __NR_chmod
#if defined(__NR_fchmodat)
func_ptr_t original_fchmodat;
#endif // __NR_fchmodat
#if defined(__NR_umask)
func_ptr_t original_umask;
#endif // __NR_umask
#if defined(__NR_statfs)
func_ptr_t original_statfs;
#endif // __NR_statfs

#if defined(__NR_openat)
func_ptr_t original_openat;
asmlinkage long new_openat(const struct pt_regs *regs)
{
	long fd = 0;
	int flags = 0;
	char *user_msg = NULL;

	HOOK_BEGIN;

	user_msg = kmalloc(USER_PATH_MAX_LEN, GFP_KERNEL);
	if (!user_msg) {
		fd = -ENOMEM;
		goto free_msg;
	}

	if (regs) {
		flags = (size_t)PT_REGS_PARM3(regs);
	}

	fd = (*original_openat)(regs);
	if (-1 < fd && (flags & O_CREAT)) {
	}
	kfree(user_msg);

free_msg:
	HOOK_COMPLETED;

	return fd;
}
#endif // __NR_openat

#if defined(__NR_write)
func_ptr_t original_write;
asmlinkage long new_write(const struct pt_regs *regs)
{
	long ret = -EBADF;
	char *user_msg = NULL;
	unsigned int fd = -1;
	const char __user *buf = NULL;
	size_t count = 0;

	HOOK_BEGIN;
	user_msg = kmalloc(USER_PATH_MAX_LEN, GFP_KERNEL);
	if (!user_msg) {
		fd = -ENOMEM;
		goto free_msg;
	}

	if (regs) {
		fd = (unsigned int)PT_REGS_PARM1(regs);
		buf = (const char __user *)PT_REGS_PARM2(regs);
		count = (size_t)PT_REGS_PARM3(regs);
	}
	ret = (*original_write)(regs);
	if (ret >= 0) {
	}

	kfree(user_msg);

free_msg:
	HOOK_COMPLETED;

	return ret;
}
#endif // __NR_write

#if defined(__NR_rename)
func_ptr_t original_rename;
asmlinkage long new_rename(const struct pt_regs *regs)
{
	long ret = 0;
	char *user_msg = NULL;
	char *old_name = NULL;
	const char __user *oldname = NULL;
	const char __user *newname = NULL;

	HOOK_BEGIN;
	user_msg = kmalloc(USER_PATH_MAX_LEN * 2, GFP_KERNEL);
	if (!user_msg) {
		ret = -ENOMEM;
		goto free_msg;
	}
	old_name = user_msg + USER_PATH_MAX_LEN;

	if (regs) {
		oldname = (const char __user *)PT_REGS_PARM1(regs);
		newname = (const char __user *)PT_REGS_PARM2(regs);
	}
	get_file_real_path(AT_FDCWD, oldname, old_name, USER_PATH_MAX_LEN - 1);
	get_file_real_path(AT_FDCWD, newname, user_msg, USER_PATH_MAX_LEN - 1);

	ret = (*original_rename)(regs);
	if (-1 < ret) {
	}

	kfree(user_msg);

free_msg:
	HOOK_COMPLETED;

	return ret;
}
#endif // __NR_rename

#if defined(__NR_renameat)
func_ptr_t original_renameat;
asmlinkage long new_renameat(const struct pt_regs *regs)
{
	long ret = 0;
	char *user_msg = NULL;
	char *old_name = NULL;
	int olddfd = AT_FDCWD;
	const char __user *oldname = NULL;
	int newdfd = AT_FDCWD;
	const char __user *newname = NULL;

	HOOK_BEGIN;
	user_msg = kmalloc(USER_PATH_MAX_LEN * 2, GFP_KERNEL);
	if (!user_msg) {
		ret = -ENOMEM;
		goto free_msg;
	}
	old_name = user_msg + USER_PATH_MAX_LEN;
	if (regs) {
		olddfd = (int)PT_REGS_PARM1(regs);
		oldname = (const char __user *)PT_REGS_PARM2(regs);
		newdfd = (int)PT_REGS_PARM3(regs);
		newname = (const char __user *)PT_REGS_PARM4(regs);
	}

	get_file_real_path(olddfd, oldname, old_name, USER_PATH_MAX_LEN - 1);
	get_file_real_path(newdfd, newname, user_msg, USER_PATH_MAX_LEN - 1);

	ret = (*original_renameat)(regs);
	if (-1 < ret) {
	}
	kfree(user_msg);

free_msg:
	HOOK_COMPLETED;

	return ret;
}
#endif // __NR_renameat

#if defined(__NR_renameat2)
func_ptr_t original_renameat2;
asmlinkage long new_renameat2(const struct pt_regs *regs)
{
	long ret = 0;
	char *user_msg = NULL;
	char *old_name = NULL;
	int olddfd = AT_FDCWD;
	const char __user *oldname = NULL;
	int newdfd = AT_FDCWD;
	const char __user *newname = NULL;
	int flags = 0;

	HOOK_BEGIN;
	user_msg = kmalloc(USER_PATH_MAX_LEN * 2, GFP_KERNEL);
	if (!user_msg) {
		ret = -ENOMEM;
		goto free_msg;
	}
	old_name = user_msg + USER_PATH_MAX_LEN;
	if (regs) {
		olddfd = (int)PT_REGS_PARM1(regs);
		oldname = (const char __user *)PT_REGS_PARM2(regs);
		newdfd = (int)PT_REGS_PARM3(regs);
		newname = (const char __user *)PT_REGS_PARM4(regs);
		flags = (int)PT_REGS_PARM5(regs);
	}

	get_file_real_path(olddfd, oldname, old_name, USER_PATH_MAX_LEN - 1);
	get_file_real_path(newdfd, newname, user_msg, USER_PATH_MAX_LEN - 1);

	ret = (*original_renameat2)(regs);
	if (-1 < ret) {
		if (flags & RENAME_NOREPLACE) {
		} else if (flags & RENAME_WHITEOUT) {
		} else if (flags & RENAME_EXCHANGE) {
		}
	}
	kfree(user_msg);

free_msg:
	HOOK_COMPLETED;

	return ret;
}
#endif // __NR_renameat2

#if defined(__NR_link)
func_ptr_t original_link;
asmlinkage long new_link(const struct pt_regs *regs)
{
	long ret = 0;
	char *user_msg = NULL;
	const char __user *oldname = NULL;
	const char __user *newname = NULL;

	HOOK_BEGIN;
	user_msg = kmalloc(USER_PATH_MAX_LEN, GFP_KERNEL);
	if (!user_msg) {
		ret = -ENOMEM;
		goto free_msg;
	}
	if (regs) {
		oldname = (const char __user *)PT_REGS_PARM1(regs);
		newname = (const char __user *)PT_REGS_PARM2(regs);
	}
	get_file_real_path(AT_FDCWD, newname, user_msg, USER_PATH_MAX_LEN - 1);
	ret = (*original_link)(regs);
	if (-1 < ret) {
	}
	kfree(user_msg);

free_msg:
	HOOK_COMPLETED;

	return ret;
}
#endif // __NR_link

#if defined(__NR_symlink)
func_ptr_t original_symlink;
asmlinkage long new_symlink(const struct pt_regs *regs)
{
	long ret = 0;
	char *user_msg = NULL;
	const char __user *oldname = NULL;
	const char __user *newname = NULL;

	HOOK_BEGIN;
	user_msg = kmalloc(USER_PATH_MAX_LEN, GFP_KERNEL);
	if (!user_msg) {
		ret = -ENOMEM;
		goto free_msg;
	}
	if (regs) {
		oldname = (const char __user *)PT_REGS_PARM1(regs);
		newname = (const char __user *)PT_REGS_PARM2(regs);
	}
	get_file_real_path(AT_FDCWD, newname, user_msg, USER_PATH_MAX_LEN - 1);
	ret = (*original_symlink)(regs);
	if (-1 < ret) {
	}
	kfree(user_msg);

free_msg:
	HOOK_COMPLETED;

	return ret;
}
#endif // __NR_symlink

#if defined(__NR_linkat)
func_ptr_t original_linkat;
asmlinkage long new_linkat(const struct pt_regs *regs)
{
	long ret = 0;
	char *user_msg = NULL;
	int olddfd = AT_FDCWD;
	const char __user *oldname = NULL;
	int newdfd = AT_FDCWD;
	const char __user *newname = NULL;
	int flags = 0;

	HOOK_BEGIN;
	user_msg = kmalloc(USER_PATH_MAX_LEN, GFP_KERNEL);
	if (!user_msg) {
		ret = -ENOMEM;
		goto free_msg;
	}
	if (regs) {
		olddfd = (int)PT_REGS_PARM1(regs);
		oldname = (const char __user *)PT_REGS_PARM2(regs);
		newdfd = (int)PT_REGS_PARM3(regs);
		newname = (const char __user *)PT_REGS_PARM4(regs);
		flags = (int)PT_REGS_PARM5(regs);
	}
	get_file_real_path(newdfd, newname, user_msg, USER_PATH_MAX_LEN - 1);
	ret = (*original_linkat)(regs);
	if (-1 < ret) {
	}
	kfree(user_msg);

free_msg:
	HOOK_COMPLETED;

	return ret;
}
#endif // __NR_linkat

#if defined(__NR_symlinkat)
func_ptr_t original_symlinkat;
asmlinkage long new_symlinkat(const struct pt_regs *regs)
{
	long ret = 0;
	char *user_msg = NULL;
	const char __user *oldname = NULL;
	int newdfd = AT_FDCWD;
	const char __user *newname = NULL;

	HOOK_BEGIN;
	user_msg = kmalloc(USER_PATH_MAX_LEN, GFP_KERNEL);
	if (!user_msg) {
		ret = -ENOMEM;
		goto free_msg;
	}
	if (regs) {
		oldname = (const char __user *)PT_REGS_PARM1(regs);
		newdfd = (int)PT_REGS_PARM2(regs);
		newname = (const char __user *)PT_REGS_PARM3(regs);
	}
	get_file_real_path(newdfd, newname, user_msg, USER_PATH_MAX_LEN - 1);
	ret = (*original_symlinkat)(regs);
	if (-1 < ret) {
	}
	kfree(user_msg);

free_msg:
	HOOK_COMPLETED;

	return ret;
}
#endif // __NR_symlinkat

#if defined(__NR_unlink)
func_ptr_t original_unlink;
asmlinkage long new_unlink(const struct pt_regs *regs)
{
	long ret = 0;
	char *user_msg = NULL;
	const char __user *pathname = NULL;

	HOOK_BEGIN;
	user_msg = kmalloc(USER_PATH_MAX_LEN, GFP_KERNEL);
	if (!user_msg) {
		ret = -ENOMEM;
		goto free_msg;
	}
	if (regs) {
		pathname = (const char __user *)PT_REGS_PARM1(regs);
	}
	get_file_real_path(AT_FDCWD, pathname, user_msg, USER_PATH_MAX_LEN - 1);
	ret = (*original_unlink)(regs);
	if (-1 < ret) {
	}
	kfree(user_msg);

free_msg:
	HOOK_COMPLETED;

	return ret;
}
#endif // __NR_unlink

#if defined(__NR_unlinkat)
func_ptr_t original_unlinkat;
asmlinkage long new_unlinkat(const struct pt_regs *regs)
{
	long ret = 0;
	char *user_msg = NULL;
	int dfd = AT_FDCWD;
	const char __user *pathname = NULL;
	int flag = 0;

	HOOK_BEGIN;
	user_msg = kmalloc(USER_PATH_MAX_LEN, GFP_KERNEL);
	if (!user_msg) {
		ret = -ENOMEM;
		goto free_msg;
	}
	if (regs) {
		dfd = (int)PT_REGS_PARM1(regs);
		pathname = (const char __user *)PT_REGS_PARM2(regs);
		flag = (int)PT_REGS_PARM3(regs);
	}

	get_file_real_path(dfd, pathname, user_msg, USER_PATH_MAX_LEN - 1);
	ret = (*original_unlinkat)(regs);
	if (-1 < ret) {
	}
	kfree(user_msg);

free_msg:
	HOOK_COMPLETED;
	return ret;
}
#endif // __NR_unlinkat

#if defined(__NR_mkdir)
func_ptr_t original_mkdir;
asmlinkage long new_mkdir(const struct pt_regs *regs)
{
	long ret = 0;
	char *user_msg = NULL;
	const char __user *pathname = NULL;
	umode_t mode = 0;

	HOOK_BEGIN;
	user_msg = kmalloc(USER_PATH_MAX_LEN, GFP_KERNEL);
	if (!user_msg) {
		ret = -ENOMEM;
		goto free_msg;
	}
	if (regs) {
		pathname = (const char __user *)PT_REGS_PARM1(regs);
		mode = (umode_t)PT_REGS_PARM2(regs);
	}
	get_file_real_path(AT_FDCWD, pathname, user_msg, USER_PATH_MAX_LEN - 1);
	ret = (*original_mkdir)(regs);
	if (-1 < ret) {
	}
	kfree(user_msg);

free_msg:

	HOOK_COMPLETED;

	return ret;
}
#endif // __NR_mkdir

#if defined(__NR_mkdirat)
func_ptr_t original_mkdirat;
asmlinkage long new_mkdirat(const struct pt_regs *regs)
{
	long ret = 0;
	char *user_msg = NULL;
	int dfd = AT_FDCWD;
	const char __user *pathname = NULL;
	umode_t mode = 0;

	HOOK_BEGIN;
	user_msg = kmalloc(USER_PATH_MAX_LEN, GFP_KERNEL);
	if (!user_msg) {
		ret = -ENOMEM;
		goto free_msg;
	}
	if (regs) {
		dfd = (int)PT_REGS_PARM1(regs);
		pathname = (const char __user *)PT_REGS_PARM2(regs);
		mode = (umode_t)PT_REGS_PARM3(regs);
	}
	get_file_real_path(dfd, pathname, user_msg, USER_PATH_MAX_LEN - 1);
	ret = (*original_mkdirat)(regs);
	if (-1 < ret) {
	}
	kfree(user_msg);

free_msg:
	HOOK_COMPLETED;

	return ret;
}
#endif // __NR_mkdirat

#if defined(__NR_rmdir)
func_ptr_t original_rmdir;
asmlinkage long new_rmdir(const struct pt_regs *regs)
{
	long ret = 0;
	char *user_msg = NULL;
	const char __user *pathname = NULL;

	HOOK_BEGIN;
	user_msg = kmalloc(USER_PATH_MAX_LEN, GFP_KERNEL);
	if (!user_msg) {
		ret = -ENOMEM;
		goto free_msg;
	}
	if (regs) {
		pathname = (const char __user *)PT_REGS_PARM1(regs);
	}
	get_file_real_path(AT_FDCWD, pathname, user_msg, USER_PATH_MAX_LEN - 1);
	ret = (*original_rmdir)(regs);
	if (-1 < ret) {
	}
	kfree(user_msg);

free_msg:
	HOOK_COMPLETED;

	return ret;
}
#endif // __NR_rmdir

#if defined(__NR_pwrite64)
func_ptr_t original_pwrite64;
asmlinkage long new_pwrite64(const struct pt_regs *regs)
{
	long ret = -EBADF;
	char *user_msg = NULL;
	unsigned int fd = AT_FDCWD;
	const char __user *buf = NULL;
	size_t count = 0;

	HOOK_BEGIN;
	user_msg = kmalloc(USER_PATH_MAX_LEN, GFP_KERNEL);
	if (!user_msg) {
		ret = -ENOMEM;
		goto free_msg;
	}
	if (regs) {
		fd = (unsigned int)PT_REGS_PARM1(regs);
		buf = (const char __user *)PT_REGS_PARM2(regs);
		count = (size_t)PT_REGS_PARM3(regs);
	}

	ret = (*original_pwrite64)(regs);
	if (-1 < ret) {
	}
	kfree(user_msg);

free_msg:
	HOOK_COMPLETED;

	return ret;
}
#endif // __NR_pwrite64

#if defined(__NR_truncate)
func_ptr_t original_truncate;
asmlinkage long new_truncate(const struct pt_regs *regs)
{
	long ret = 0;
	char *user_msg = NULL;
	const char __user *path = NULL;
	long length = 0;

	HOOK_BEGIN;
	user_msg = kmalloc(USER_PATH_MAX_LEN, GFP_KERNEL);
	if (!user_msg) {
		ret = -ENOMEM;
		goto free_msg;
	}
	if (regs) {
		path = (const char __user *)PT_REGS_PARM1(regs);
		length = (unsigned long)PT_REGS_PARM2(regs);
	}
	ret = (*original_truncate)(regs);
	get_file_real_path(AT_FDCWD, path, user_msg, USER_PATH_MAX_LEN - 1);
	if (-1 < ret) {
	}
	kfree(user_msg);

free_msg:
	HOOK_COMPLETED;

	return ret;
}
#endif // __NR_truncate

#if defined(__NR_ftruncate)
func_ptr_t original_ftruncate;
asmlinkage long new_ftruncate(const struct pt_regs *regs)
{
	long ret = -EBADF;
	char *user_msg = NULL;
	unsigned int fd = -1;
	unsigned long length = 0;

	HOOK_BEGIN;
	user_msg = kmalloc(USER_PATH_MAX_LEN, GFP_KERNEL);
	if (!user_msg) {
		ret = -ENOMEM;
		goto free_msg;
	}
	if (regs) {
		fd = PT_REGS_PARM1(regs);
		length = (unsigned long)PT_REGS_PARM2(regs);
	}
	ret = (*original_ftruncate)(regs);
	if (-1 < ret) {
	}
	kfree(user_msg);

free_msg:
	HOOK_COMPLETED;

	return ret;
}
#endif // __NR_ftruncate

static struct mutex hook_mutex;
static void **sys_call_table_ptr = NULL;

#if defined(__x86_64__)
static void *hook_vmalloc_map(void *addr);
static int hook_vmalloc_unmap(void *addr);
#endif

#if defined(__aarch64__) || defined(__arm__)
void (*update_mapping_prot)(phys_addr_t phys, unsigned long virt,
			    phys_addr_t size, pgprot_t prot);
unsigned long start_rodata, end_rodata;
#define section_size (end_rodata - start_rodata)

static void enable_wirte_protection(void);
static void disable_wirte_protection(void);
#endif

int hook_api_init(void)
{
	long ret = 0;
	HOOK_INIT;
	sys_call_table_ptr = (void **)kallsyms_lookup_name("sys_call_table");
	if (sys_call_table_ptr == NULL) {
		pr_info("error: get sys call table failure.\n");
		return -EINVAL;
	}

#if defined(__aarch64__) || defined(__arm__)
	update_mapping_prot =
		(void *)kallsyms_lookup_name("update_mapping_prot");
	start_rodata = (unsigned long)kallsyms_lookup_name("__start_rodata");
	end_rodata = (unsigned long)kallsyms_lookup_name("__end_rodata");
	pr_info("update_mapping_prot:%lx, start_rodata:%lx, end_rodata:%lx.\n",
		update_mapping_prot, start_rodata, end_rodata);
#endif

#if defined(__NR_openat)
	original_openat = sys_call_table_ptr[__NR_openat];
	pr_info("info: get system call openat.\n");
#endif
#if defined(__NR_write)
	original_write = sys_call_table_ptr[__NR_write];
	pr_info("info: get system call write.\n");
#endif
#if defined(__NR_rename)
	original_rename = sys_call_table_ptr[__NR_rename];
	pr_info("info: get system call rename.\n");
#endif
#if defined(__NR_renameat)
	original_renameat = sys_call_table_ptr[__NR_renameat];
	pr_info("info: get system call renameat.\n");
#endif
#if defined(__NR_renameat2)
	original_renameat2 = sys_call_table_ptr[__NR_renameat2];
	pr_info("info: get system call renameat2.\n");
#endif
#if defined(__NR_link)
	original_link = sys_call_table_ptr[__NR_link];
	pr_info("info: get system call link.\n");
#endif
#if defined(__NR_linkat)
	original_linkat = sys_call_table_ptr[__NR_linkat];
	pr_info("info: get system call linkat.\n");
#endif
#if defined(__NR_unlinkat)
	original_unlinkat = sys_call_table_ptr[__NR_unlinkat];
	pr_info("info: get system call unlinkat.\n");
#endif
#if defined(__NR_symlink)
	original_symlink = sys_call_table_ptr[__NR_symlink];
	pr_info("info: get system call symlink.\n");
#endif
#if defined(__NR_symlinkat)
	original_symlinkat = sys_call_table_ptr[__NR_symlinkat];
	pr_info("info: get system call symlinkat.\n");
#endif
#if defined(__NR_unlink)
	original_unlink = sys_call_table_ptr[__NR_unlink];
	pr_info("info: get system call unlink.\n");
#endif
#if defined(__NR_mkdir)
	original_mkdir = sys_call_table_ptr[__NR_mkdir];
	pr_info("info: get system call mkdir.\n");
#endif
#if defined(__NR_mkdirat)
	original_mkdirat = sys_call_table_ptr[__NR_mkdirat];
	pr_info("info: get system call mkdirat.\n");
#endif
#if defined(__NR_rmdir)
	original_rmdir = sys_call_table_ptr[__NR_rmdir];
	pr_info("info: get system call rmdir.\n");
#endif
	// original_access = sys_call_table_ptr[__NR_access];
#if defined(__NR_faccessat)
	original_faccessat = sys_call_table_ptr[__NR_faccessat];
	pr_info("info: get system call faccessat.\n");
#endif
#if defined(__NR_pwrite64)
	original_pwrite64 = sys_call_table_ptr[__NR_pwrite64];
	pr_info("info: get system call pwrite64.\n");
#endif
#if defined(__NR_truncate)
	original_truncate = sys_call_table_ptr[__NR_truncate];
	pr_info("info: get system call truncate.\n");
#endif
#if defined(__NR_ftruncate)
	original_ftruncate = sys_call_table_ptr[__NR_ftruncate];
	pr_info("info: get system call ftruncate.\n");
#endif
#if defined(__NR_chmod)
	original_chmod = sys_call_table_ptr[__NR_chmod];
	pr_info("info: get system call chmod.\n");
#endif
#if defined(__NR_fchmodat)
	original_fchmodat = sys_call_table_ptr[__NR_fchmodat];
	pr_info("info: get system call fchmodat.\n");
#endif
#if defined(__NR_umask)
	original_umask = sys_call_table_ptr[__NR_umask];
	pr_info("info: get system call umask.\n");
#endif
#if defined(__NR_statfs)
	original_statfs = sys_call_table_ptr[__NR_statfs];
	pr_info("info: get system call statfs.\n");
#endif

	return ret;
}

void hook_api_exit(void)
{
	mutex_lock(&hook_mutex);
	sys_call_table_ptr = (void **)kallsyms_lookup_name("sys_call_table");
	if (sys_call_table_ptr == NULL) {
		pr_info("error: get sys call table failure.\n");
		return;
	}
#if defined(__x86_64__)
	sys_call_table_ptr = hook_vmalloc_map(sys_call_table_ptr);
	if (sys_call_table_ptr == NULL) {
		pr_info("erorr: mapping to virtual page failure.\n");
		return;
	}
#endif

#if defined(__aarch64__) || defined(__arm__)
	disable_wirte_protection();
#endif

#if defined(__NR_openat)
	sys_call_table_ptr[__NR_openat] = original_openat;
	pr_info("info: restore hook openat.\n");
#endif

#if defined(__NR_write)
	sys_call_table_ptr[__NR_write] = original_write;
	pr_info("info: restore hook write.\n");
#endif
#if defined(__NR_pwrite64)
	sys_call_table_ptr[__NR_pwrite64] = original_pwrite64;
	pr_info("info: restore hook pwrite64.\n");
#endif
#if defined(__NR_mkdir)
	sys_call_table_ptr[__NR_mkdir] = original_mkdir;
	pr_info("info: restore hook mkdir.\n");
#endif
#if defined(__NR_mkdirat)
	sys_call_table_ptr[__NR_mkdirat] = original_mkdirat;
	pr_info("info: restore hook mkdirat.\n");
#endif
#if defined(__NR_rmdir)
	sys_call_table_ptr[__NR_rmdir] = original_rmdir;
	pr_info("info: restore hook rmdir.\n");
#endif
#if defined(__NR_rename)
	sys_call_table_ptr[__NR_rename] = original_rename;
	pr_info("info: restore hook rename.\n");
#endif
#if defined(__NR_renameat)
	sys_call_table_ptr[__NR_renameat] = original_renameat;
	pr_info("info: restore hook renameat.\n");
#endif
#if defined(__NR_renameat2)
	sys_call_table_ptr[__NR_renameat2] = original_renameat2;
	pr_info("info: restore hook renameat2.\n");
#endif
#if defined(__NR_link)
	sys_call_table_ptr[__NR_link] = original_link;
	pr_info("info: restore hook link.\n");
#endif
#if defined(__NR_linkat)
	sys_call_table_ptr[__NR_linkat] = original_linkat;
	pr_info("info: restore hook linkat.\n");
#endif
#if defined(__NR_symlink)
	sys_call_table_ptr[__NR_symlink] = original_symlink;
	pr_info("info: restore hook symlink.\n");
#endif
#if defined(__NR_symlinkat)
	sys_call_table_ptr[__NR_symlinkat] = original_symlinkat;
	pr_info("info: restore hook symlinkat.\n");
#endif
#if defined(__NR_unlink)
	sys_call_table_ptr[__NR_unlink] = original_unlink;
	pr_info("info: restore hook unlink.\n");
#endif
#if defined(__NR_unlinkat)
	sys_call_table_ptr[__NR_unlinkat] = original_unlinkat;
	pr_info("info: restore hook unlinkat.\n");
#endif
#if defined(__NR_truncate)
	sys_call_table_ptr[__NR_truncate] = original_truncate;
	pr_info("info: restore hook truncate.\n");
#endif
#if defined(__NR_ftruncate)
	sys_call_table_ptr[__NR_ftruncate] = original_ftruncate;
	pr_info("info: restore hook ftruncate.\n");
#endif

#if defined(__x86_64__)
	hook_vmalloc_unmap(sys_call_table_ptr);
#endif

#if defined(__aarch64__) || defined(__arm__)
	enable_wirte_protection();
#endif

	mutex_unlock(&hook_mutex);

	mutex_destroy(&hook_mutex);

	while (!HOOK_SAFTY_EXIT) {
		pr_info("---- sys hook count: %lld", HOOK_COUNT);
		ssleep(10);
	}
}

int hook_sys_call(void)
{
	long ret = 0;

	mutex_init(&hook_mutex);

	mutex_lock(&hook_mutex);
	sys_call_table_ptr = (void **)kallsyms_lookup_name("sys_call_table");
	if (sys_call_table_ptr == NULL) {
		pr_info("error: get sys call table failure.\n");
		return -EINVAL;
	}

#if defined(__x86_64__)
	sys_call_table_ptr = hook_vmalloc_map(sys_call_table_ptr);
	if (sys_call_table_ptr == NULL) {
		pr_info("erorr: mapping to virtual page failure.\n");
		return -EINVAL;
	}
#endif

#if defined(__aarch64__) || defined(__arm__)
	disable_wirte_protection();
#endif

#if defined(__NR_openat)
	sys_call_table_ptr[__NR_openat] = new_openat;
	pr_info("info: hook openat.\n");
#endif

#if defined(__NR_write)
	sys_call_table_ptr[__NR_write] = new_write;
	pr_info("info: hook write.\n");
#endif
#if defined(__NR_pwrite64)
	sys_call_table_ptr[__NR_pwrite64] = new_pwrite64;
	pr_info("info: hook pwrite64.\n");
#endif
#if defined(__NR_mkdir)
	sys_call_table_ptr[__NR_mkdir] = new_mkdir;
	pr_info("info: hook mkdir.\n");
#endif
#if defined(__NR_mkdirat)
	sys_call_table_ptr[__NR_mkdirat] = new_mkdirat;
	pr_info("info: hook mkdirat.\n");
#endif
#if defined(__NR_rmdir)
	sys_call_table_ptr[__NR_rmdir] = new_rmdir;
	pr_info("info: hook rmdir.\n");
#endif
#if defined(__NR_rename)
	sys_call_table_ptr[__NR_rename] = new_rename;
	pr_info("info: hook rename.\n");
#endif
#if defined(__NR_renameat)
	sys_call_table_ptr[__NR_renameat] = new_renameat;
	pr_info("info: hook renameat.\n");
#endif
#if defined(__NR_renameat2)
	sys_call_table_ptr[__NR_renameat2] = new_renameat2;
	pr_info("info: hook renameat2.\n");
#endif
#if defined(__NR_link)
	sys_call_table_ptr[__NR_link] = new_link;
	pr_info("info: hook link.\n");
#endif
#if defined(__NR_linkat)
	sys_call_table_ptr[__NR_linkat] = new_linkat;
	pr_info("info: hook linkat.\n");
#endif
#if defined(__NR_symlink)
	sys_call_table_ptr[__NR_symlink] = new_symlink;
	pr_info("info: hook symlink.\n");
#endif
#if defined(__NR_symlinkat)
	sys_call_table_ptr[__NR_symlinkat] = new_symlinkat;
	pr_info("info: hook symlinkat.\n");
#endif
#if defined(__NR_unlink)
	sys_call_table_ptr[__NR_unlink] = new_unlink;
	pr_info("info: hook unlink.\n");
#endif
#if defined(__NR_unlinkat)
	sys_call_table_ptr[__NR_unlinkat] = new_unlinkat;
	pr_info("info: hook unlinkat.\n");
#endif
#if defined(__NR_truncate)
	sys_call_table_ptr[__NR_truncate] = new_truncate;
	pr_info("info: hook truncate.\n");
#endif
#if defined(__NR_ftruncate)
	sys_call_table_ptr[__NR_ftruncate] = new_ftruncate;
	pr_info("info: hook ftruncate.\n");
#endif

#if defined(__x86_64__)
	hook_vmalloc_unmap(sys_call_table_ptr);
#endif

#if defined(__aarch64__) || defined(__arm__)
	enable_wirte_protection();
#endif

	mutex_unlock(&hook_mutex);

	return ret;
}

#if defined(__x86_64__)
static void *hook_vmalloc_map(void *addr)
{
	unsigned int level = 0;
	pte_t *pte = lookup_address((unsigned long)addr, &level);
	if (!pte) {
		return NULL;
	}

	if (pte->pte & ~_PAGE_RW) {
		pte->pte |= _PAGE_RW;
	}
	return addr;
}

static int hook_vmalloc_unmap(void *addr)
{
	unsigned int level = 0;
	pte_t *pte = lookup_address((unsigned long)addr, &level);
	if (!pte) {
		return -1;
	}

	pte->pte = pte->pte & ~_PAGE_RW;
	return 0;
}
#endif

#if defined(__aarch64__) || defined(__arm__)
static void disable_wirte_protection(void)
{
	update_mapping_prot(__pa_symbol(start_rodata),
			    (unsigned long)start_rodata, section_size,
			    PAGE_KERNEL);
	return;
}

static void enable_wirte_protection(void)
{
	update_mapping_prot(__pa_symbol(start_rodata),
			    (unsigned long)start_rodata, section_size,
			    PAGE_KERNEL_RO);
	return;
}
#endif
