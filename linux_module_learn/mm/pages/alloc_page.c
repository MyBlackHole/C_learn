#include <linux/init.h>
#include <linux/module.h>
#include <linux/gfp.h>
#include <linux/mm_types.h>
#include <linux/mm.h>

struct page *pages = NULL;

int __init alloc_pages_init(void)
{
	pages = alloc_pages(GFP_KERNEL, 3); //分配8个物理页
	if (!pages) {
		return -ENOMEM;
	} else {
		printk("alloc_pages Successfully! \n");
		printk("page_address(pages) = 0x%lx\n",
		       (unsigned long)page_address(pages));
	}
	return 0;
}

void __exit alloc_pages_exit(void)
{
	if (pages) {
		__free_pages(pages, 4); //释放所分配的8个页
		printk("__free_pages ok! \n");
	}
	printk("exit\n");
}

module_init(alloc_pages_init);
module_exit(alloc_pages_exit);
MODULE_LICENSE("GPL");
