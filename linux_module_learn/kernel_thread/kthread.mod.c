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
	"\x14\x00\x00\x00\xff\x83\x43\x64"
	"pcpu_hot\0\0\0\0"
	"\x10\x00\x00\x00\x7e\x3a\x2c\x12"
	"_printk\0"
	"\x20\x00\x00\x00\xfe\x05\x50\xcc"
	"msleep_interruptible\0\0\0\0"
	"\x1c\x00\x00\x00\x6e\x64\xf7\xb3"
	"kthread_should_stop\0"
	"\x1c\x00\x00\x00\xca\x39\x82\x5b"
	"__x86_return_thunk\0\0"
	"\x20\x00\x00\x00\x2c\x8a\xd8\x48"
	"__SCT__preempt_schedule\0"
	"\x18\x00\x00\x00\xd7\xf0\x58\x79"
	"kthread_stop\0\0\0\0"
	"\x14\x00\x00\x00\xd5\xe3\x7d\x01"
	"nr_cpu_ids\0\0"
	"\x1c\x00\x00\x00\x71\x22\x5a\x5a"
	"__cpu_online_mask\0\0\0"
	"\x18\x00\x00\x00\xd9\xe8\xa1\x53"
	"_find_next_bit\0\0"
	"\x28\x00\x00\x00\xb3\x1c\xa2\x87"
	"__ubsan_handle_out_of_bounds\0\0\0\0"
	"\x20\x00\x00\x00\x87\x24\xb9\x16"
	"kthread_create_on_node\0\0"
	"\x18\x00\x00\x00\x13\x70\xdc\xc9"
	"kthread_bind\0\0\0\0"
	"\x18\x00\x00\x00\x19\x69\x88\x06"
	"wake_up_process\0"
	"\x14\x00\x00\x00\xbb\x6d\xfb\xbd"
	"__fentry__\0\0"
	"\x18\x00\x00\x00\x6a\xb7\x61\x9e"
	"module_layout\0\0\0"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "E4E3D98B1C991BA78019371");
