/**
 * @file 2.c
 * @author {BlackHole} ({1358244533@qq.com})
 * @brief
 * @date 2021/08/18 21:55:40
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <errno.h>
#include <fcntl.h>
#include <linux/rtc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>

int demo_timer_main()
{
	unsigned long index = 0;
	unsigned long data = 0;
	int retval = 0;
	// 实时指针设备 /dev/rtc
	int fd_tmp = open("/dev/rtc", O_RDONLY);

	if (fd_tmp < 0) {
		perror("open");
		exit(errno);
	}

	/* Set the freq as 4Hz */
	/* 设置频率为4Hz */
	if (ioctl(fd_tmp, RTC_IRQP_SET, 0) < 0) {
		perror("ioctl(fd, RTC_IRQP_SET, 0)");
		close(fd_tmp);
		exit(errno);
	}

	/* Enable periodic interrupts */
	// 启用中断
	if (ioctl(fd_tmp, RTC_PIE_ON, 0) < 0) {
		perror("ioctl(fd, RTC_PIE_ON, 0)");
		close(fd_tmp);
		exit(errno);
	}

	for (index = 0; index < 100; index++) {
		if (read(fd_tmp, &data, sizeof(unsigned long)) < 0) {
			perror("read");
			close(fd_tmp);
			exit(errno);
		}
		printf("timer\n");
	}

	/* Disable periodic interrupts */
	// 停用中断
	ioctl(fd_tmp, RTC_PIE_OFF, 0);
	close(fd_tmp);

	return EXIT_SUCCESS;
}
