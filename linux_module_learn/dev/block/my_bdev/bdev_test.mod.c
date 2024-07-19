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
	__section("__versions") = "\x1c\x00\x00\x00\xa7\x27\x0a\x72"
				  "__register_blkdev\0\0\0"
				  "\x20\x00\x00\x00\xb1\x29\xa9\x47"
				  "blk_mq_alloc_tag_set\0\0\0\0"
				  "\x1c\x00\x00\x00\xa6\x64\xf1\x67"
				  "__blk_mq_alloc_disk\0"
				  "\x18\x00\x00\x00\x40\x00\x2e\xb7"
				  "device_add_disk\0"
				  "\x14\x00\x00\x00\x42\xdb\x77\xa5"
				  "del_gendisk\0"
				  "\x1c\x00\x00\x00\xdc\x59\xa4\xb5"
				  "unregister_blkdev\0\0\0"
				  "\x14\x00\x00\x00\x16\x85\xc7\x58"
				  "put_disk\0\0\0\0"
				  "\x1c\x00\x00\x00\xf1\x3e\x2e\x82"
				  "blk_mq_free_tag_set\0"
				  "\x14\x00\x00\x00\xbb\x6d\xfb\xbd"
				  "__fentry__\0\0"
				  "\x1c\x00\x00\x00\xca\x39\x82\x5b"
				  "__x86_return_thunk\0\0"
				  "\x10\x00\x00\x00\x7e\x3a\x2c\x12"
				  "_printk\0"
				  "\x18\x00\x00\x00\xc1\x35\x7c\x15"
				  "module_layout\0\0\0"
				  "\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "");

MODULE_INFO(srcversion, "5DFD8C0D0D92E16528DFA32");
