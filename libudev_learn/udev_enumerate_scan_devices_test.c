/* udev_example2.c
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
 * This example will enumerate all devices belonging to 'block' subsystem
 * and omit partitions and loop devices using libudev API.
 *
 */

#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 512

int demo_udev_enumerate_scan_devices_main()
{
	struct udev *udev;
	struct udev_device *dev;
	struct udev_enumerate *enumerate;
	struct udev_list_entry *devices;
	struct udev_list_entry *devListEntry;

	/* create udev object */
	udev = udev_new();
	if (!udev) {
		fprintf(stderr, "Cannot create udev context.\n");
		return 1;
	}

	/* create enumerate object */
	enumerate = udev_enumerate_new(udev);
	if (!enumerate) {
		fprintf(stderr, "Cannot create enumerate context.\n");
		return 1;
	}

	udev_enumerate_add_match_subsystem(enumerate, "block");
	udev_enumerate_scan_devices(enumerate);

	/* fillup device list */
	devices = udev_enumerate_get_list_entry(enumerate);
	if (!devices) {
		fprintf(stderr, "Failed to get device list.\n");
		return 1;
	}

	udev_list_entry_foreach(devListEntry, devices)
	{
		const char *path;
		const char *tmp;
		unsigned long long diskSize = 0;
		unsigned short int blockSize = BLOCK_SIZE;

		path = udev_list_entry_get_name(devListEntry);
		dev = udev_device_new_from_syspath(udev, path);

		/* skip if device/disk is a partition or loop device */
		if (strncmp(udev_device_get_devtype(dev), "partition", 9) !=
			    0 &&
		    strncmp(udev_device_get_sysname(dev), "loop", 4) != 0) {
			printf("I: DEVNODE=%s\n", udev_device_get_devnode(dev));
			printf("I: KERNEL=%s\n", udev_device_get_sysname(dev));
			printf("I: DEVPATH=%s\n", udev_device_get_devpath(dev));
			printf("I: DEVTYPE=%s\n", udev_device_get_devtype(dev));

			tmp = udev_device_get_sysattr_value(dev, "size");
			if (tmp) {
				diskSize = strtoull(tmp, NULL, 10);
			}

			tmp = udev_device_get_sysattr_value(
				dev, "queue/logical_block_size");
			if (tmp) {
				blockSize = atoi(tmp);
			}

			printf("I: DEVSIZE=");
			if (strncmp(udev_device_get_sysname(dev), "sr", 2) !=
			    0) {
				printf("%lld GB\n",
				       (diskSize * blockSize) / 1000000000);
			} else {
				printf("n/a\n");
			}
		}

		/* free dev */
		udev_device_unref(dev);
	}
	/* free enumerate */
	udev_enumerate_unref(enumerate);
	/* free udev */
	udev_unref(udev);

	return 0;
}
