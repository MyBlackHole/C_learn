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
	{ 0x92997ed8, "_printk" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x30a80826, "__kfifo_from_user" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0x4578f528, "__kfifo_to_user" },
	{ 0xee0cb502, "mount_single" },
	{ 0x356dd422, "simple_fill_super" },
	{ 0x631837b1, "new_inode" },
	{ 0x9a994cf7, "current_task" },
	{ 0x64abbdc6, "current_time" },
	{ 0x344b8d06, "init_special_inode" },
	{ 0x62a89b6b, "simple_dir_inode_operations" },
	{ 0x723dff33, "simple_dir_operations" },
	{ 0xd76b83ff, "inc_nlink" },
	{ 0xcaaf3511, "d_instantiate" },
	{ 0xd9b85ef6, "lockref_get" },
	{ 0x57bc19d2, "down_write" },
	{ 0x754d539c, "strlen" },
	{ 0x2890ae6f, "lookup_one_len" },
	{ 0xce807a25, "up_write" },
	{ 0xb67a0943, "register_filesystem" },
	{ 0x376faf2b, "kern_mount" },
	{ 0xb7d65fec, "unregister_filesystem" },
	{ 0xc73fbeb5, "simple_release_fs" },
	{ 0x14195285, "kill_litter_super" },
	{ 0x541a6db8, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "6254DCC2CB797DE25994C5B");
