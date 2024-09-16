#include <stdio.h>
#include <stdlib.h>

enum {
	OPTION_VERSION = 'v',
	OPTION_VERSION_CAP = 'V',
	OPTION_DEBUG = 1000,
	OPTION_SYSTEMD_CGROUP,
	OPTION_CGROUP_MANAGER,
	OPTION_LOG,
	OPTION_LOG_FORMAT,
	OPTION_ROOT,
	OPTION_ROOTLESS
};

enum log_level {
	LOG1, // 0
	LOG2,
	LOG3,
};

int demo_enum_main(void)
{
	enum log_level level = LOG1;
	printf("%d\n", OPTION_CGROUP_MANAGER);
	printf("%d\n", LOG1);
	printf("%d\n", level);
	return EXIT_SUCCESS;
}

// out:
// xmake run grammar enum
// 1002
// 0
// 0
