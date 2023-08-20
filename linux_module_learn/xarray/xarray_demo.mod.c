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


static const char ____versions[]
__used __section("__versions") =
	"\x18\x00\x00\x00\x74\x2b\x9d\x7f"
	"kmalloc_caches\0\0"
	"\x18\x00\x00\x00\x6a\x1d\xe7\x99"
	"kmalloc_trace\0\0\0"
	"\x10\x00\x00\x00\xda\xfa\x66\x91"
	"strncpy\0"
	"\x14\x00\x00\x00\x2f\x28\x3e\x5b"
	"xa_store\0\0\0\0"
	"\x1c\x00\x00\x00\xca\x39\x82\x5b"
	"__x86_return_thunk\0\0"
	"\x10\x00\x00\x00\x7e\x3a\x2c\x12"
	"_printk\0"
	"\x10\x00\x00\x00\x24\x5c\xa2\x8f"
	"xa_find\0"
	"\x14\x00\x00\x00\x81\xa9\x45\x07"
	"xa_erase\0\0\0\0"
	"\x10\x00\x00\x00\xba\x0c\x7a\x03"
	"kfree\0\0\0"
	"\x18\x00\x00\x00\x4b\x91\x36\xdf"
	"xa_find_after\0\0\0"
	"\x1c\x00\x00\x00\x56\xb9\x19\x0a"
	"__stack_chk_fail\0\0\0\0"
	"\x10\x00\x00\x00\x6d\x3e\x5a\xa8"
	"xa_load\0"
	"\x14\x00\x00\x00\xbb\x6d\xfb\xbd"
	"__fentry__\0\0"
	"\x18\x00\x00\x00\xc1\x35\x7c\x15"
	"module_layout\0\0\0"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "AAC4C19E219D44C475A509B");
