#include <arpa/inet.h>
#include <netinet/in.h>
#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int ret;
	char errbuf[1024];

	pcap_if_t *all_dev;

	// 函数用来查找网络设备
	ret = pcap_findalldevs(&all_dev, errbuf);

	if (ret < 0) {
		printf("errbuf:%s ret:%d\n", errbuf, ret);
		return EXIT_FAILURE;
	}

	for (pcap_if_t *pdev = all_dev; pdev; pdev = pdev->next) {
		printf("name:%s, description:%s\n", pdev->name,
		       pdev->description);
		// printf("name:%s, description:%s, addresses:%s\n", pdev->name,
		//        pdev->description,
		//        inet_ntoa(((struct sockaddr_in *)pdev->addresses)->sin_addr));
	}

	pcap_freealldevs(all_dev);

	return EXIT_SUCCESS;
}
