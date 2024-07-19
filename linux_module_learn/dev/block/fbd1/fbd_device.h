#ifndef _FBD_DRIVER_H
#define _FBD_DRIVER_H

#include <linux/init.h>
#include <linux/module.h> /* 写内核模块都需要包含该头文件 */
#include <linux/blkdev.h> /* 写内核块设备驱动必须要包含的三个头文件：blkdev.h, bio.h, genhd.h */
#include <linux/bio.h>

/* 用来表示扇区的比特数，对于块设备，扇区是其最小的传输和存储单元，默认扇区大小是512字节，这里的9代表将512换算为二进制需要多少位描述，很快可以算出来：2＾9
 * = 512 */
#define SECTOR_BITS (9)
#define DEV_NAME_LEN 32 /* 过滤块设备的名字最长为32个字节 */

/* 过滤块设备大小是512M，1左移20位是1M，再乘以扇区大小即为512M */
#define DEV_SIZE (512UL << 20)
/* 给驱动程序注册的名字"fbd_driver" */
#define DRIVER_NAME "filter driver"
/* 过滤块设备驱动程序创建的过滤块设备名字"fbd1_dev" */
#define DEVICE1_NAME "fbd1_dev"
#define DEVICE1_MINOR 0
/* 过滤块设备驱动程序创建的过滤块设备名字"fbd2_dev" */
#define DEVICE2_NAME "fbd2_dev"
#define DEVICE2_MINOR 1

/* 结构体fbd_dev，三个成员：queue指针成员，disk指针，设备大小，该结构体描述我们创建的过滤块设备
 */
struct fbd_dev {
	struct request_queue *queue;
	struct gendisk *disk;
	sector_t size; /* device size in Bytes */
};

#endif
