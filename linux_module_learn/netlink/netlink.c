#include <linux/init.h>
#include <linux/module.h>
#include <linux/netlink.h>
#include <linux/types.h>
#include <net/sock.h>

#define NETLINK_TEST 30
#define MSG_LEN 100
#define USER_PORT 66

struct sock *nlsk;

extern struct net init_net;

int send_usrmsg(char *pbuf, uint16_t len)
{
	struct sk_buff *nl_skb;
	struct nlmsghdr *nlh; // 消息头部

	int ret;
	// 创建sk_buff
	nl_skb = nlmsg_new(len, GFP_ATOMIC);
	if (!nl_skb) {
		printk("netlink alloc failure\n");
		return -1;
	}

	/* 设置netlink消息头部 */
	nlh = nlmsg_put(nl_skb, 0, 0, NETLINK_TEST, len, 0);
	if (nlh == NULL) {
		printk("nlmsg_put failaure \n");
		nlmsg_free(nl_skb);
		return -1;
	}

	/* 拷贝数据发送 */
	memcpy(nlmsg_data(nlh), pbuf, len);
	/* 单播发送 */
	ret = netlink_unicast(nlsk, nl_skb, USER_PORT, MSG_DONTWAIT);

	return ret;
}

static void netlink_rcv_msg(struct sk_buff *skb)
{
	struct nlmsghdr *nlh;
	char *umsg = NULL;
	char *kmsg = "hello users";
	// 从skb中获取data字段，并转换成nlh进行读取
	nlh = nlmsg_hdr(skb);

	/*if (skb->len > NLMSG_SPACE(0))*/

	// 读取nlh后面的数据部分
	umsg = NLMSG_DATA(nlh);
	if (umsg) {
		printk("kernel recv from user: %s\n", umsg);
		printk("port id :%d\n", NETLINK_CB(skb).portid);
		send_usrmsg(kmsg, strlen(kmsg)); // 给用户态发消息
	}
}
struct netlink_kernel_cfg cfg = {
	.input = netlink_rcv_msg,
};

static int __init test_netlink_init(void)
{
	nlsk = (struct sock *)netlink_kernel_create(&init_net, NETLINK_TEST,
						    &cfg);
	if (!nlsk) {
		printk("netlink_kernel_create failure\n");
		return -1;
	}
	return 0;
}

static void __exit test_netlink_exit(void)
{
	if (nlsk) {
		netlink_kernel_release(nlsk);
		nlsk = NULL;
	}

	printk("exit......\n");
}
MODULE_LICENSE("GPL");
module_init(test_netlink_init);
module_exit(test_netlink_exit);
