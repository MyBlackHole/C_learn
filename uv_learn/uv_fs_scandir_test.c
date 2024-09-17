#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

int demo_fs_scandir_main(int argc, char *argv[])
{
	struct uv_fs_s req;
	struct uv_dirent_s entry;
	int num = 0;
	int ret = 0;

	num = uv_fs_scandir(NULL, &req, "/tmp", 0, NULL);
	for (int i = 0; i < num; i++) {
		const char *filename;
		ret = uv_fs_scandir_next(&req, &entry);
		assert(ret == 0); /* Can't fail in libuv */

		filename = entry.name;
		printf("%s, ret=%d\n", filename, ret);
	}
	return EXIT_SUCCESS;
}
