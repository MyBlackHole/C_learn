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
	"\x10\x00\x00\x00\x7e\x3a\x2c\x12"
	"_printk\0"
	"\x1c\x00\x00\x00\xca\x39\x82\x5b"
	"__x86_return_thunk\0\0"
	"\x14\x00\x00\x00\xbb\x6d\xfb\xbd"
	"__fentry__\0\0"
	"\x14\x00\x00\x00\xbc\x35\x87\x14"
	"pcpu_hot\0\0\0\0"
	"\x30\x00\x00\x00\x49\xbb\x88\x24"
	"__tracepoint_mmap_lock_start_locking\0\0\0\0"
	"\x14\x00\x00\x00\xa1\x19\x8b\x66"
	"down_read\0\0\0"
	"\x30\x00\x00\x00\xc3\xb2\x4e\x9d"
	"__tracepoint_mmap_lock_acquire_returned\0"
	"\x14\x00\x00\x00\xc6\x31\xcf\x9a"
	"mas_find\0\0\0\0"
	"\x28\x00\x00\x00\xb3\x0c\xc4\x63"
	"__tracepoint_mmap_lock_released\0"
	"\x10\x00\x00\x00\xa2\x54\xb9\x53"
	"up_read\0"
	"\x14\x00\x00\x00\xe3\x31\x00\x58"
	"find_vpid\0\0\0"
	"\x14\x00\x00\x00\x75\xeb\x27\xd6"
	"pid_task\0\0\0\0"
	"\x28\x00\x00\x00\xcd\x9c\xa7\x1d"
	"__mmap_lock_do_trace_released\0\0\0"
	"\x30\x00\x00\x00\xb9\xe0\x06\x38"
	"__mmap_lock_do_trace_acquire_returned\0\0\0"
	"\x2c\x00\x00\x00\x2f\x4c\x94\xe8"
	"__mmap_lock_do_trace_start_locking\0\0"
	"\x1c\x00\x00\x00\x56\xb9\x19\x0a"
	"__stack_chk_fail\0\0\0\0"
	"\x18\x00\x00\x00\x98\x68\xb0\xc7"
	"param_ops_int\0\0\0"
	"\x18\x00\x00\x00\xc1\x35\x7c\x15"
	"module_layout\0\0\0"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "7B3AD9699456448CFE4FA22");
