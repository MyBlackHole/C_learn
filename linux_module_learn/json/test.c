// SPDX-License-Identifier: GPL-2.0
// Authors: Emanuele Santini <emanuele.santini.88@gmail.com>

/* Hoto use it:
 * insmod test.ko
 * read dmesg command output
 * rmmod test.ko
 */

#include "kjson.h"
#include <linux/module.h>

int __init test_init(void)
{
	struct file *config_fp = NULL;

	struct kjson_object_t *TestNumberObj;

	struct kjson_container *my_json;
	struct kjstring_t *dmp;

	printk(KERN_INFO "ok\n");

	// Open the config file
	config_fp = filp_open("/tmp/config.json", O_RDONLY, 0);
	if (!config_fp) {
		printk(KERN_INFO "open error\n");
		return -1;
	}

	my_json = kjson_file_parse(config_fp);
	if (!my_json) {
		printk(KERN_INFO "parse error\n");
		return -1;
	}

	filp_close(config_fp, NULL);

	TestNumberObj = kjson_lookup_object(my_json, "TestNumber");
	if (!TestNumberObj) {
		printk(KERN_INFO "TestNumber not found\n");
		return -1;
	}
	printk(KERN_INFO "TestNumber: %lld\n", kjson_as_integer(TestNumberObj));

	kjson_push_string_array(my_json, "RandomString", "String1", "String2",
				"ALotOfStrings");

	dmp = kjson_dump(my_json);
	printk(KERN_INFO "New json: %s\n", kjstring_str(dmp));

	kjson_delete_container(my_json);

	return 0;
}

void __exit test_exit(void)
{
	printk("exit ok\n");
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
