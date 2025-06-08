/* udev_example1.c
 *
 * Copyright (C) 2014-2021 Robert Milasan <robert@linux-source.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This example will get basic information about a specified network
 * device using libudev API.
 *
 */

#include <libudev.h>
#include <stdio.h>

#define SYSPATH "/sys/class/net"
#define NUM 128

// ./out/obj/libudev_learn/udev_new_test lo
int demo_udev_new_main(int argc, char *argv[])
{
	struct udev *udev;
	struct udev_device *dev;
	struct udev_device *devParent;
	char device[NUM];

	/* verify that we have an argument, like eth0, otherwise fail */
	if (!argv[1]) {
		fprintf(stderr,
			"Missing network interface name.\nexample: %s eth0\n",
			argv[0]);
		return 1;
	}

	/* build device path out of SYSPATH macro and argv[1] */
	snprintf(device, sizeof(device), "%s/%s", SYSPATH, argv[1]);

	/* create udev object */
	udev = udev_new();
	if (!udev) {
		fprintf(stderr, "Cannot create udev context.\n");
		return 1;
	}

	/* get device based on path */
	dev = udev_device_new_from_syspath(udev, device);
	if (!dev) {
		fprintf(stderr, "Failed to get device.\n");
		return 1;
	}

	printf("I: DEVNAME=%s\n", udev_device_get_sysname(dev));
	printf("I: DEVPATH=%s\n", udev_device_get_devpath(dev));
	printf("I: MACADDR=%s\n",
	       udev_device_get_sysattr_value(dev, "address"));

	devParent = udev_device_get_parent(dev);
	if (devParent) {
		printf("I: DRIVER=%s\n", udev_device_get_driver(devParent));
	}

	/* free dev */
	udev_device_unref(dev);

	/* free udev */
	udev_unref(udev);

	return 0;
}
