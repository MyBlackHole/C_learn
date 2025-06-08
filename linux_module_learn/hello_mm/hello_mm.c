#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/types.h>

#define MONITOR_ARRAY_SIZE 12800
/*#define MONITOR_ARRAY_SIZE 1280*/
/*#define MONITOR_ARRAY_SIZE 128*/
#define PATH_MAX_LEN 512
#define CONF_PATH_MAX_LEN PATH_MAX_LEN
#define APP_NAME_LEN 128
#define EVENT_BUF_SIZE PATH_MAX_LEN * 2
#define LOGBUF 1024

struct dir_info {
	int dir_name_len;
	char dir_name[PATH_MAX_LEN];
	struct list_head node;
};

typedef struct dir_info dir_info_t;

struct monitor_meta {
	dir_info_t monitor;
	char config_path[CONF_PATH_MAX_LEN];
	char config_path_tmp[CONF_PATH_MAX_LEN];
	char base_log_path[CONF_PATH_MAX_LEN];
	char app_name[APP_NAME_LEN];
};

typedef struct monitor_meta monitor_meta_t;

struct monitor_config {
	struct kobject kobj;
	struct mutex config_lock;

	struct list_head node;

	char err_info[LOGBUF];

	bool hook_status;
	uint64_t timetamp_ns;
	uint64_t start_time;
	uint64_t log_file_index;
	uint64_t io_event_index;
	uint64_t app_log_file_index;

	char io_event_buf[EVENT_BUF_SIZE];
	char log_out_file[CONF_PATH_MAX_LEN];
	struct file *log_fp;
	size_t file_remaining_size;
	struct mutex log_io_event_mutex;
	monitor_meta_t meta;
};

static struct monitor_config monitor_config_obj[MONITOR_ARRAY_SIZE] = { 0 };

static int __init hello_mm_init(void)
{
	int i = 0;
	pr_info("hello world!\n");
	for (i = 0; i < MONITOR_ARRAY_SIZE; i++) {
		pr_info("monitor_config_obj[%d] mm size: %ld, pointer: %p\n", i,
			sizeof(monitor_config_obj[i]), &monitor_config_obj[i]);
		pr_info("hook status: %d", monitor_config_obj[i].hook_status);
	}
	pr_info("monitor_config_obj mm size: %ld, pointer: %p\n",
		sizeof(monitor_config_obj), monitor_config_obj);
	return 0;
}
static void __exit hello_mm_exit(void)
{
	printk("good bye!\n");
}
module_init(hello_mm_init);
module_exit(hello_mm_exit);
MODULE_LICENSE("GPL");
