#include <linux/module.h>
#include <linux/printk.h>
#include <linux/errno.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/platform_device.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/in.h>
#include <linux/skbuff.h>
#include <linux/spinlock.h>
#include <linux/string.h>
#include <linux/init.h>
#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/gfp.h>
#include <linux/io.h>
#include <asm/irq.h>
#include <linux/atomic.h>

static struct net_device *vnet_dev;

// 有数据帧要发送时，内核会调用该函数
static int vnet_send_packet(struct sk_buff *skb, struct net_device *dev)
{
	// 统计已发送的数据包
	dev->stats.tx_packets++;
	// 统计已发送的字节
	dev->stats.tx_bytes += skb->len;
	// 释放数据帧
	dev_kfree_skb(skb);
	return 0;
}

// 驱动程序支持的操作
static struct net_device_ops vnet_ops = {
	// 发送数据帧
	.ndo_start_xmit = vnet_send_packet,
};

static int __init virt_net_init(void)
{
	printk(KERN_ERR "%s,%d\n", __FUNCTION__, __LINE__);

	//1、分配一个 net_device 结构体
	//生成一个net_device结构体，对其成员赋值并返回该结构体的指针
	vnet_dev = alloc_netdev(0, "vnet%d", NET_NAME_UNKNOWN, ether_setup);

	//2、设置
	//网络设备的操作集，这个参数一定要有！否则驱动无法加载
	vnet_dev->netdev_ops = &vnet_ops;

	//3、注册
	register_netdev(vnet_dev);

	//4、硬件操作

	return 0;
}

static void __exit virt_net_exit(void)
{
	unregister_netdev(vnet_dev);
	free_netdev(vnet_dev);
}

module_init(virt_net_init);
module_exit(virt_net_exit);
MODULE_AUTHOR("zfeng");
MODULE_LICENSE("GPL");
