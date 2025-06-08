#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#define CHECK_LOG_COUNT 3
#define CHECK_LOG_BUF_SIZE 1024
static char g_log_bufs[CHECK_LOG_COUNT][CHECK_LOG_BUF_SIZE] = { 0 };
static int g_log_index = 0;
static char g_log_buf[CHECK_LOG_BUF_SIZE] = { 0 };

#define CHECK_INDEX_COUNT 10;
static char index_buf[CHECK_LOG_COUNT];
static int index_buf_index = 0;

#ifndef LOG_INFO
#define LOG_INFO(__fmt__, ...) \
	__printk__(__FILE__, __LINE__, __func__, __fmt__, ##__VA_ARGS__)
#endif

int __printk__(const char *fname, const int line, const char *func,
	       const char *format, ...)
{
	int ret = 0;
	int i = 0;
	va_list args;
	(void)fname;
	(void)line;
	(void)func;

	va_start(args, format);
	ret = vsnprintf(g_log_buf, CHECK_LOG_BUF_SIZE, format, args);
	va_end(args);

	for (i = 0; i < CHECK_LOG_COUNT; i++) {
		if (strcmp(g_log_buf, g_log_bufs[i]) == 0) {
			index_buf[index_buf_index] = i + 48;
			index_buf_index =
				(index_buf_index + 1) % CHECK_INDEX_COUNT;
			goto return__;
		}
	}

	printk("[%s] - %s", index_buf, g_log_buf);
	index_buf_index = 0;
	index_buf[index_buf_index] = '\0';

return__:
	memcpy(g_log_bufs[g_log_index], g_log_buf, CHECK_LOG_BUF_SIZE);
	g_log_index = (g_log_index + 1) % CHECK_LOG_COUNT;
	return ret;
}

static int __init log_init(void)
{
	LOG_INFO("hello world!\n");
	LOG_INFO("Black\n");
	LOG_INFO("hello world! hello world\n");
	LOG_INFO("hello world! hello world\n");
	LOG_INFO("Black\n");
	LOG_INFO("Black\n");
	LOG_INFO("hello world!\n");
	LOG_INFO("hello world!\n");
	LOG_INFO("hello world!\n");
	LOG_INFO("hello world!\n");
	LOG_INFO("hello world!\n");
	LOG_INFO("hello world!\n");
	LOG_INFO("hello world!\n");
	return 0;
}
static void __exit log_exit(void)
{
	printk("good bye!\n");
}
module_init(log_init);
module_exit(log_exit);
MODULE_LICENSE("GPL");
