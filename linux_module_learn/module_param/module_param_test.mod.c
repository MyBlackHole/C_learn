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

__visible struct module __this_module __section(".gnu.linkonce.this_module") = {
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

static const char ____versions[] __used
	__section("__versions") = "\x14\x00\x00\x00\xbb\x6d\xfb\xbd"
				  "__fentry__\0\0"
				  "\x10\x00\x00\x00\x7e\x3a\x2c\x12"
				  "_printk\0"
				  "\x1c\x00\x00\x00\xca\x39\x82\x5b"
				  "__x86_return_thunk\0\0"
				  "\x18\x00\x00\x00\x98\x68\xb0\xc7"
				  "param_ops_int\0\0\0"
				  "\x18\x00\x00\x00\xc1\x35\x7c\x15"
				  "module_layout\0\0\0"
				  "\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "");

MODULE_INFO(srcversion, "3DEE3503965AC31765A1FAD");
