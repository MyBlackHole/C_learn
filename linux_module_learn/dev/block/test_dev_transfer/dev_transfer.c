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

#define BLK_NAME         "ram_blk"
#define BLK_MAJOR        222
#define DISK_SECTOR_SIZE 512                               // 每扇区大小
#define DISK_SECTOR      1024                              // 总扇区数，
#define DISK_SIZE        (DISK_SECTOR_SIZE * DISK_SECTOR)  // 总大小，共0.5M

typedef struct  // 设备结构体
{
    unsigned char        *data;
    struct request_queue *queue;
    struct gendisk       *gd;
} disk_dev;

disk_dev device;  // 定义设备结构体

//--------------------------------------------------------------------------
// 在硬盘等带柱面扇区等的设备上使用request，可以整理队列。但是ramdisk等可以
// 使用make_request
static int disk_make_request(struct request_queue *queue, struct bio *bio)
{
    struct bvec_iter iter;
    char            *mem_pbuf;
    char            *disk_pbuf;
    disk_dev        *pdevice;
    struct bio_vec   pbvec;

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
    bio_for_each_segment(pbvec, bio, iter)
    {
        // 获得实际内存地址
        mem_pbuf = kmap(pbvec.bv_page) + pbvec.bv_offset;
        switch (bio_data_dir(bio))
        {  // 读写
            case READ:
                memcpy(mem_pbuf, disk_pbuf, pbvec.bv_len);
                break;
            case WRITE:
                memcpy(disk_pbuf, mem_pbuf, pbvec.bv_len);
                break;
            default:
                kunmap(pbvec.bv_page);
                goto fail;
        }
        // 清除映射
        kunmap(pbvec.bv_page);
        disk_pbuf += pbvec.bv_len;
    }
    bio_endio(bio);  // 这个函数2.6.25和2.6.4是不一样的，
    return 0;
fail:
    bio_io_error(bio);  // 这个函数2.6.25和2.6.4是不一样的，
    return 0;
}

int blk_open(struct gendisk *disk, blk_mode_t mode) { return 0; }

void blk_release(struct gendisk *disk) { ; }

int blk_ioctl(struct block_device *dev, fmode_t no, unsigned cmd,
              unsigned long arg)
{
    return -ENOTTY;
}

static struct block_device_operations blk_fops = {
    .owner   = THIS_MODULE,
    .open    = blk_open,
    .release = blk_release,
    .ioctl   = blk_ioctl,
};

int disk_init(void)
{
    int error;
    // 注册驱动
    if (!register_blkdev(BLK_MAJOR, BLK_NAME))
    {
        ;
    }
    {
        printk("register blk_dev succeed\n");
    }

    device.data = (unsigned char *)vmalloc(DISK_SIZE);

    printk("make_request succeed\n");

    device.gd               = blk_alloc_disk(GFP_KERNEL);  // 生成gendisk
    device.queue            = device.gd->queue;            // 赋值 queue
    device.gd->major        = BLK_MAJOR;                   // 主设备号
    device.gd->first_minor  = 0;                           // 此设备号
    device.gd->fops         = &blk_fops;     // 块文件结构体变量
    device.gd->queue        = device.queue;  // 请求队列
    device.gd->private_data = &device;
    sprintf(device.gd->disk_name, "disk%c", 'a');  // 名字
    set_capacity(device.gd, DISK_SECTOR);          // 设置大小
    error = add_disk(device.gd);                   // 注册块设备信息
    if (error)
    {
        goto out_put_disk;
    }
    printk("gendisk succeed\n");
    return 0;
out_put_disk:
    put_disk(device.gd);
    return error;
}

void disk_exit(void)
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
