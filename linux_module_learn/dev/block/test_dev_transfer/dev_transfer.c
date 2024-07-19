#include <asm/uaccess.h>
#include <linux/blkdev.h>
#include <linux/blkpg.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/fs.h>
#include <linux/hdreg.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/vmalloc.h>

#define BLK_NAME "ram_blk"
#define BLK_MAJOR 222
#define DISK_SECTOR_SIZE 512 // 每扇区大小
#define DISK_SECTOR 1024 // 总扇区数，
#define DISK_SIZE (DISK_SECTOR_SIZE * DISK_SECTOR) // 总大小，共0.5M

typedef struct // 设备结构体
{
	unsigned char *data;
	struct request_queue *queue;
	struct gendisk *gd;
} disk_dev;

disk_dev device; // 定义设备结构体

void submit_bio(struct bio *bio)
{
	struct bvec_iter iter;
	char *mem_pbuf;
	char *disk_pbuf;
	disk_dev *pdevice;
	struct bio_vec vec;

	// /*在遍历段之前先判断要传输数据的总长度大小是否超过范围*/
	// iter = bio->bi_iter.bi_sector * DISK_SECTOR_SIZE + bio->bi_iter.bi_size;
	// if ((int)iter > DISK_SIZE)  // 判断是否超出范围
	//     goto fail;

	// 得到设备结构体
	pdevice = (disk_dev *)bio->bi_bdev->bd_disk->private_data;
	// 得到要读写的起始位置
	disk_pbuf = pdevice->data + bio->bi_iter.bi_sector * DISK_SECTOR_SIZE;

	/*开始遍历这个bio中的每个bio_vec*/
	// 循环分散的内存segment
	bio_for_each_segment(vec, bio, iter) {
		// 获得实际内存地址
		mem_pbuf = kmap(vec.bv_page) + vec.bv_offset;
		switch (bio_data_dir(bio)) { // 读写
		case READ:
			memcpy(mem_pbuf, disk_pbuf, vec.bv_len);
			break;
		case WRITE:
			memcpy(disk_pbuf, mem_pbuf, vec.bv_len);
			break;
		default:
			kunmap(vec.bv_page);
			goto fail;
		}
		// 清除映射
		kunmap(vec.bv_page);
		disk_pbuf += vec.bv_len;
	}
	bio_endio(bio); // 这个函数2.6.25和2.6.4是不一样的，
fail:
	bio_io_error(bio); // 这个函数2.6.25和2.6.4是不一样的，
}

static struct block_device_operations blk_fops = {
	.submit_bio = submit_bio,
	.owner = THIS_MODULE,
};

static int __init disk_init(void)
{
	int error;
	// 注册驱动
	error = register_blkdev(BLK_MAJOR, BLK_NAME);
	if (error) {
		goto blk_dev_fail;
	}

	device.data = (unsigned char *)vmalloc(DISK_SIZE);

	printk("make_request succeed\n");

	device.gd = blk_alloc_disk(NULL, NUMA_NO_NODE); // 生成gendisk
	device.gd->major = BLK_MAJOR; // 主设备号
	device.gd->first_minor = 0; // 此设备号
	device.gd->fops = &blk_fops; // 块文件结构体变量
	device.gd->private_data = &device;
	sprintf(device.gd->disk_name, "disk%c", 'a'); // 名字
	set_capacity(device.gd, DISK_SECTOR); // 设置大小
	error = add_disk(device.gd); // 注册块设备信息
	if (error) {
		goto out_put_disk;
	}
	printk("gendisk succeed\n");
	return 0;

blk_dev_fail:
	printk("register blk_dev succeed\n");
	unregister_blkdev(BLK_MAJOR, BLK_NAME);
out_put_disk:
	put_disk(device.gd);
	return error;
}

static void __exit disk_exit(void)
{
	del_gendisk(device.gd);
	put_disk(device.gd);
	unregister_blkdev(BLK_MAJOR, BLK_NAME);
	vfree(device.data);
	printk("free succeed\n");
}

module_init(disk_init);
module_exit(disk_exit);

MODULE_LICENSE("Dual BSD/GPL");
