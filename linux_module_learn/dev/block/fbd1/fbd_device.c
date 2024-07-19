/**
 *  fbd-driver - filter block device driver
 *  Author: Talk@studio
 *  Modified by abin
 **/

#include "fbd_device.h"

static int fbd_driver_major = 0;

static struct fbd_dev fbd_dev1 = { NULL };
static struct fbd_dev fbd_dev2 = { NULL };

static int fbddev_open(struct inode *inode, struct file *file);
static int fbddev_close(struct inode *inode, struct file *file);

static struct block_device_operations disk_fops = {
	.open = (void *)fbddev_open,
	.release = (void *)fbddev_close,
	.owner = THIS_MODULE,
};

/* 块设备被打开时调用该函数 */
static int fbddev_open(struct inode *inode, struct file *file)
{
	printk("device is opened by:[%s]\n", current->comm);
	return 0;
}

/* 块设备被关闭时调用该函数 */
static int fbddev_close(struct inode *inode, struct file *file)
{
	printk("device is closed by:[%s]\n", current->comm);
	return 0;
}

/* 仓库的加工函数，在dev_create中被调用 */
// 参数1是我们的关卡请求队列，参数2是上层准备好的盒子bio请求描述结构体指针
static int make_request(struct request_queue *request_queue, struct bio *bio)
{
	struct fbd_dev *dev = (struct fbd_dev *)request_queue->queuedata;

	printk("device [%s] recevied [%s] io request, "
	       "access on dev sector[%llu], length is [%u] sectors.\n",
	       dev->disk->disk_name,
	       bio_data_dir(bio) == READ ? "read" : "write",
	       (long long)bio->bi_iter.bi_sector, bio_sectors(bio));

	// 结束一个bio请求
	bio_endio(bio);

	return 0;
}

/* 创建过滤设备的函数，在init函数中被调用 */
static int dev_create(struct fbd_dev *dev, char *dev_name, int major, int minor)
{
	int ret = 0;

	/* init fbd_dev */
	dev->size = DEV_SIZE;

	/* 申请仓库gendisk，返回值为gendisk结构体 */
	dev->disk = blk_alloc_disk(GFP_KERNEL);
	if (!dev->disk) {
		printk("alloc diskerror");
		ret = -ENOMEM;
		goto err_out1;
	}

	/* 建立关卡，关卡申请后，可以用也可以不用，但必须申请 */
	dev->queue = dev->disk->queue;

	if (!dev->queue) {
		printk("alloc queueerror");
		ret = -ENOMEM;
		goto err_out2;
	}

	/* 仓库加工函数，即：请求处理函数make_request，第一参数是刚申请到的请求队列，第二个参数是我们写好的make_request函数名*/

	/* init queue */
	blk_queue_make_request(dev->queue, (void *)make_request);
	dev->queue->queuedata = dev;

	/* 给gendisk的disk_name成员赋值，也就是给仓库取名字 */
	/* init gendisk */
	strncpy(dev->disk->disk_name, dev_name, DEV_NAME_LEN);
	/* 把申请到的门牌号赋值给disk的成员major */
	dev->disk->major = major;
	/* 赋值了一个次设备号 */
	dev->disk->first_minor = minor;
	/* 为gendisk的文件操作函数赋值了一个函数指针集结构体 */
	dev->disk->fops = &disk_fops;
	/* 设置设备的容量大小为512M */
	set_capacity(dev->disk, (dev->size >> SECTOR_BITS));

	/* 把申请的queue地址保存在disk中，这样仓库和关卡就绑定在一起了*/
	/* bind queue to disk */
	dev->disk->queue = dev->queue;

	/*告诉内核我们的仓库需要审核一下，如果通过，那仓库就建好了*/

	/* add disk to kernel */
	add_disk(dev->disk);
	return 0;

err_out2:
	put_disk(dev->disk);
err_out1:
	return ret;
}

static void dev_delete(struct fbd_dev *dev, char *name)
{
	printk("delete the device [%s]!\n", name);

	blk_cleanup_queue(dev->queue);
	del_gendisk(dev->disk);
	put_disk(dev->disk);
}

/* 内核模块入口，也是构建块设备驱动的核心部分 */
static int __init fbd_driver_init(void)
{
	int ret;
	/* 第一个参数是初始化的major号，第二参数是块设备驱动的名字。第一参数0时,系统会从它自己管理的情况表上查找是否有可用的号码，如果有就分配，作为regiser_blkdev的返回值*/
	/* register fbd driver, get the driver major number */
	fbd_driver_major = register_blkdev(fbd_driver_major, DRIVER_NAME);

	if (fbd_driver_major < 0) {
		printk("get majorfail");
		ret = -EIO;
		goto err_out1;
	}

	/* create the first device */
	ret = dev_create(&fbd_dev1, DEVICE1_NAME, fbd_driver_major,
			 DEVICE1_MINOR);

	if (ret) {
		printk("create device[%s] failed!\n", DEVICE1_NAME);
		goto err_out2;
	}

	/* create the second device */
	ret = dev_create(&fbd_dev2, DEVICE2_NAME, fbd_driver_major,
			 DEVICE2_MINOR);

	if (ret) {
		printk("create device[%s] failed!\n", DEVICE2_NAME);
		goto err_out3;
	}
	return ret;

err_out3:
	dev_delete(&fbd_dev1, DEVICE1_NAME);
err_out2:
	unregister_blkdev(fbd_driver_major, DRIVER_NAME);
err_out1:
	return ret;
}

static void __exit fbd_driver_exit(void)
{
	/* delete the two devices */
	dev_delete(&fbd_dev2, DEVICE2_NAME);
	dev_delete(&fbd_dev1, DEVICE1_NAME);

	/* unregister fbd driver */
	unregister_blkdev(fbd_driver_major, DRIVER_NAME);
	printk("block device driver exit successfuly!\n");
}

module_init(fbd_driver_init);
module_exit(fbd_driver_exit);
MODULE_LICENSE("GPL");
