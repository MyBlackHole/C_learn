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

int demo_enum_main(void)
{
	printf("%d\n", OPTION_CGROUP_MANAGER);
	return EXIT_SUCCESS;
}

// out:
// 1002
