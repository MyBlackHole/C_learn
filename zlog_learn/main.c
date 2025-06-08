#include <stdlib.h>
#include <stdio.h>
#include <zlog.h>

int demo_main_main(int argc, char **argv)
{
	int rc;
	zlog_category_t *c;

	if (argc < 2) {
		printf("Usage: %s <config_file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	// 初始化 zlog
	rc = zlog_init(argv[1]);
	if (rc) {
		printf("zlog init failed\n");
		return rc;
	}

	// 获取日志分类（若分类未在配置中定义，使用默认规则）
	c = zlog_get_category("my_cat");
	if (!c) {
		printf("get category fail\n");
		zlog_fini();
		return EXIT_FAILURE;
	}

	// 记录不同级别日志
	zlog_debug(c, "This is a DEBUG message");
	zlog_info(c, "This is an INFO message");
	zlog_error(c, "This is an ERROR message");

	// 关闭 zlog
	zlog_fini();
	return EXIT_SUCCESS;
}

// xmake run zlog_learn main /run/media/black/Data/Documents/c/zlog_learn/zlog.conf
