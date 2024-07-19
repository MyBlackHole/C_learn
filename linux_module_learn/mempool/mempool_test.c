#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/mempool.h>
#include <linux/blkdev.h>
#include <linux/writeback.h>

static struct kmem_cache *kmem;
static mempool_t *pool = NULL;

int __init mempool_create_init(void)
{
	// 创建一个名为"my_buffer"的slab缓存
	kmem = kmem_cache_create("my_buffer", 10000, 0, SLAB_HWCACHE_ALIGN,
				 NULL);

	if (kmem == NULL) {
		printk("kmem_cache_create failed! \n");
		return 0;
	} else {
		printk("kmem_cache_create successfully! \n");

		// 基于创建的slab缓存创建一个包含5个初始元素的内存池
		pool = mempool_create(5, mempool_alloc_slab, mempool_free_slab,
				      kmem);
		if (pool == NULL) {
			printk("mempool_create failed! \n");
			return 0;
		} else {
			printk("mempool_create successfully! min_nr = %d\n",
			       pool->min_nr);
		}
	}
	return 0;
}

void __exit mempool_create_exit(void)
{
	if (pool != NULL) {
		mempool_destroy(pool); // 销毁创建的内存池
		printk("mempool_destroy succeed! \n");
	}
	if (kmem != NULL) {
		kmem_cache_destroy(kmem); // 销毁创建的slab缓存
		printk("kmem_cache_destroy succeed! \n");
	}
	printk("exit! \n");
}

MODULE_LICENSE("GPL");
module_init(mempool_create_init);
module_exit(mempool_create_exit);
