#include <linux/bitops.h>
#include <linux/blk-mq.h>
#include <linux/blkdev.h>
#include <linux/init.h>
#include <linux/major.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/pgtable.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

#define DEVICE_NAME "my_bdev"
static DEFINE_MUTEX(my_dev_mutex);
static int MY_MAJOR;
static struct gendisk *my_gendisk;

static blk_status_t my_queue_rq(struct blk_mq_hw_ctx *hctx,
				const struct blk_mq_queue_data *bd)
{
	return BLK_STS_OK;
}

static int z2_open(struct gendisk *disk, blk_mode_t mode)
{
	return 0;
}

static void z2_release(struct gendisk *disk)
{
}

static const struct block_device_operations my_fops = {
	.owner = THIS_MODULE,
	.open = z2_open,
	.release = z2_release,
};

static struct blk_mq_tag_set tag_set;

static const struct blk_mq_ops my_mq_ops = {
	.queue_rq = my_queue_rq,
};

static int __init my_init(void)
{
	int ret;
	int err;
	printk("%s: my_init", DEVICE_NAME);
	MY_MAJOR = register_blkdev(100, DEVICE_NAME);
	if (MY_MAJOR) {
		return -EBUSY;
	}
	ret = -ENOMEM;

	tag_set.ops = &my_mq_ops;
	tag_set.nr_hw_queues = 1;
	tag_set.nr_maps = 1;
	tag_set.queue_depth = 16;
	tag_set.numa_node = NUMA_NO_NODE;
	tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
	ret = blk_mq_alloc_tag_set(&tag_set);
	if (ret) {
		goto out_unregister_blkdev;
	}

	my_gendisk = blk_mq_alloc_disk(&tag_set, NULL);
	my_gendisk->major = MY_MAJOR;
	my_gendisk->first_minor = 0;
	my_gendisk->minors = 1;
	my_gendisk->flags |= GENHD_FL_NO_PART;
	my_gendisk->fops = &my_fops;
	sprintf(my_gendisk->disk_name, "my_bdev");
	err = add_disk(my_gendisk);
	if (err) {
		put_disk(my_gendisk);
	}

	return 0;

out_unregister_blkdev:
	unregister_blkdev(MY_MAJOR, DEVICE_NAME);
	return ret;
}

static void __exit my_exit(void)
{
	printk("%s: my_exit", DEVICE_NAME);
	unregister_blkdev(MY_MAJOR, DEVICE_NAME);

	del_gendisk(my_gendisk);
	put_disk(my_gendisk);

	blk_mq_free_tag_set(&tag_set);

	return;
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lakshya A Agrawal");
MODULE_DESCRIPTION("A simple device driver for XOR decryption");
