#include <linux/netlink.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define NETLINK_TEST 30
#define MSG_LEN 100
#define MAX_PLOAD 200
typedef struct _user_msg_info {
	struct nlmsghdr hdr;
	char msg[MSG_LEN];
} user_msg_info;

int main(int argc, char **argv)
{
	int sockfd;
	/*
	 struct sockaddr_nl {
	     __kernel_sa_family_t    nl_family;  // AF_NETLINK （跟AF_INET对应）
	     unsigned short  nl_pad;     // zero
	     __u32       nl_pid;     // port ID  （通信端口号）
	     __u32       nl_groups;  //multicast groups mask
	 };
	*/
	struct sockaddr_nl saddr, daddr;
	/* struct nlmsghd 是netlink消息头
	 struct nlmsghdr {
	     __u32       nlmsg_len;  // Length of message including header
	     __u16       nlmsg_type; // Message content
	     __u16       nlmsg_flags;    // Additional flags
	     __u32       nlmsg_seq;  // Sequence number
	     __u32       nlmsg_pid;  // Sending process port ID
	 };
	 */
	struct nlmsghdr *nlh;
	user_msg_info u_info;
	char *msg = "hell kernel, I am user process!";
	socklen_t len;

	// 创建socket
	sockfd = socket(AF_NETLINK, SOCK_RAW, NETLINK_TEST);

	// 初始化地址
	memset(&saddr, 0, sizeof(saddr));

	// 地址赋值
	saddr.nl_family = AF_NETLINK;
	saddr.nl_pad = 0;
	saddr.nl_pid = 66;
	saddr.nl_groups = 0;

	// 地址与sockt绑定-bind
	bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));

	// 初始化目的地址
	memset(&daddr, 0, sizeof(daddr));
	memset(&daddr, 0, sizeof(daddr));
	daddr.nl_family = AF_NETLINK;
	daddr.nl_pid = 0; // to kernel
	daddr.nl_groups = 0;

	// 初始化消息头
	nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PLOAD));
	memset(nlh, 0, sizeof(struct nlmsghdr));
	nlh->nlmsg_len = NLMSG_SPACE(MAX_PLOAD);
	nlh->nlmsg_flags = 0;
	nlh->nlmsg_type = 0;
	nlh->nlmsg_seq = 0;
	nlh->nlmsg_pid = saddr.nl_pid; // self port

	// 设置消息内容
	memcpy(NLMSG_DATA(nlh), msg, strlen(msg));

	// 发送消息
	sendto(sockfd, nlh, nlh->nlmsg_len, 0, (struct sockaddr *)&daddr,
	       sizeof(struct sockaddr_nl));
	printf("send kernel :%s", msg);

	memset(&u_info, 0, sizeof(u_info));
	len = sizeof(struct sockaddr_nl);
	// 接收消息
	recvfrom(sockfd, &u_info, sizeof(user_msg_info), 0,
		 (struct sockaddr *)&daddr, &len);
	printf("\n");
	printf("from kernel:%s\n", u_info.msg);
	close(sockfd);
	return 0;
}
