#include <stdio.h>
#include <sys/utsname.h>

int demo_uname_main()
{
	struct utsname sys_info;
	if (uname(&sys_info) == -1) {
		perror("uname");
		return 1;
	}
	printf("系统架构： %s\n", sys_info.machine);
	return 0;
}
