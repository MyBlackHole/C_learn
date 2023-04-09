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
	{ 0x6b27729b, "radix_tree_gang_lookup" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0x4e6e4b41, "radix_tree_delete" },
	{ 0xeed3c484, "__free_pages" },
	{ 0xc07351b3, "__SCT__cond_resched" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x9658af6, "debugfs_remove" },
	{ 0xfd020264, "del_gendisk" },
	{ 0xafcc7a59, "blk_cleanup_disk" },
	{ 0x37a0cba, "kfree" },
	{ 0xe64b43f, "alloc_pages" },
	{ 0x32ce3777, "radix_tree_preload" },
	{ 0xba8fbd64, "_raw_spin_lock" },
	{ 0x6fbc6a00, "radix_tree_insert" },
	{ 0xb5b54b34, "_raw_spin_unlock" },
	{ 0x4629334c, "__preempt_count" },
	{ 0x70ad75fb, "radix_tree_lookup" },
	{ 0x48d88a2c, "__SCT__preempt_schedule" },
	{ 0xf301d0c, "kmalloc_caches" },
	{ 0x35789eee, "kmem_cache_alloc_trace" },
	{ 0x656e4a6e, "snprintf" },
	{ 0x6ee466d6, "debugfs_create_u64" },
	{ 0x12657b71, "__blk_alloc_disk" },
	{ 0xa916b694, "strnlen" },
	{ 0x69acdf38, "memcpy" },
	{ 0x28447b99, "set_capacity" },
	{ 0xadf5185e, "blk_queue_physical_block_size" },
	{ 0xb7263bed, "blk_queue_flag_set" },
	{ 0xc680cb6b, "blk_queue_flag_clear" },
	{ 0x4b3a8c01, "device_add_disk" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0x8d522714, "__rcu_read_lock" },
	{ 0x2469810f, "__rcu_read_unlock" },
	{ 0x9a994cf7, "current_task" },
	{ 0x97651e6c, "vmemmap_base" },
	{ 0x7cd8d75e, "page_offset_base" },
	{ 0xbcb36fe4, "hugetlb_optimize_vmemmap_key" },
	{ 0xb00a3954, "page_endio" },
	{ 0xa25b103e, "bio_endio" },
	{ 0xa648e561, "__ubsan_handle_shift_out_of_bounds" },
	{ 0x92997ed8, "_printk" },
	{ 0xd78a52d6, "debugfs_create_dir" },
	{ 0x720a27a7, "__register_blkdev" },
	{ 0xb5a459dc, "unregister_blkdev" },
	{ 0x4fa8f1f1, "param_ops_int" },
	{ 0x64de735d, "param_ops_ulong" },
	{ 0x541a6db8, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "7A1A065965F38A5B82A375B");
