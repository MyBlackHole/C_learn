#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

int demo_fs_stat_main(int argc, char *argv[])
{
	struct uv_fs_s req;
	int ret;
	ret = uv_fs_stat(NULL, &req, "/tmp/Test", NULL);
	printf("rv=%d, %s\n", ret, strerror(-ret));
	return EXIT_SUCCESS;
}
