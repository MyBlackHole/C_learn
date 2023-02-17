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
#include <time.h>
#include <unistd.h>

int main()
{
    unsigned long i = 0;
    unsigned long data = 0;
    int retval = 0;
    int fd = open("/dev/rtc", O_RDONLY);

    if (fd < 0)
    {
        perror("open");
        exit(errno);
    }

    /* Set the freq as 4Hz */
    if (ioctl(fd, RTC_IRQP_SET, 0) < 0)
    {
        perror("ioctl(fd, RTC_IRQP_SET, 0)");
        close(fd);
        exit(errno);
    }

    /* Enable periodic interrupts */
    if (ioctl(fd, RTC_PIE_ON, 0) < 0)
    {
        perror("ioctl(fd, RTC_PIE_ON, 0)");
        close(fd);
        exit(errno);
    }

    for (i = 0; i < 100; i++)
    {
        if (read(fd, &data, sizeof(unsigned long)) < 0)
        {
            perror("read");
            close(fd);
            exit(errno);
        }
        printf("timer\n");
    }

    /* Disable periodic interrupts */
    ioctl(fd, RTC_PIE_OFF, 0);
    close(fd);

    return 0;
}
