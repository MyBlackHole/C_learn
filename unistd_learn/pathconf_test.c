#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 获取实际限制值
int demo_pathconf_main()
{
	char pathname[256] = "/home";
	printf("%s:\n", pathname);
	printf("NAME_MAX=%ld\n", pathconf(pathname, _PC_NAME_MAX));
	printf("PATH_MAX=%ld\n", pathconf(pathname, _PC_PATH_MAX));
	printf("LINK_MAX=%ld\n", pathconf(pathname, _PC_LINK_MAX));
	printf("MAX_INPUT=%ld\n", pathconf(pathname, _PC_MAX_INPUT));
	printf("MAX_CANON=%ld\n", pathconf(pathname, _PC_MAX_CANON));
	printf("PIPE_BUF=%ld\n", pathconf(pathname, _PC_PIPE_BUF));

	return EXIT_SUCCESS;
}
