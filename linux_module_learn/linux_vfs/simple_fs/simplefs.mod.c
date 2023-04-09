#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xa916b694, "strnlen" },
	{ 0x31549b2a, "__x86_indirect_thunk_r10" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0xf2b3a417, "mount_nodev" },
	{ 0x631837b1, "new_inode" },
	{ 0x1ff731c2, "init_user_ns" },
	{ 0xebdee8ef, "inode_init_owner" },
	{ 0x64abbdc6, "current_time" },
	{ 0x71cbab8b, "d_make_root" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x56b8048f, "simple_rmdir" },
	{ 0xd76b83ff, "inc_nlink" },
	{ 0x754d539c, "strlen" },
	{ 0x69acdf38, "memcpy" },
	{ 0x794f41bf, "d_add" },
	{ 0x164e020, "set_nlink" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0x3e2e998f, "simple_unlink" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0xf301d0c, "kmalloc_caches" },
	{ 0x35789eee, "kmem_cache_alloc_trace" },
	{ 0xb67a0943, "register_filesystem" },
	{ 0x92997ed8, "_printk" },
	{ 0xb7d65fec, "unregister_filesystem" },
	{ 0x37a0cba, "kfree" },
	{ 0x5a8f7dae, "kill_anon_super" },
	{ 0x541a6db8, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "04FB9BE8C9934EDB9920037");
