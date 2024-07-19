#include <glob.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <tbox/libc/string/string.h>
#include <tbox/algorithm/rfor.h>
#include <tbox/platform/file.h>
#include <tbox/prefix/malloc.h>
#include <tbox/prefix/type.h>
#include "tbox/container/list.h"

int err_func(const char *errpath, int errno);

int glob_recursive(const char *pattern, int flags, tb_list_ref_t list)
{
	glob_t globres;
	int index;
	tb_int_t ret = EXIT_SUCCESS;
	tb_file_info_t info;
	tb_char_t path[PATH_MAX] = { 0 };

	tb_strcpy(path, pattern);

	if (!tb_file_info(pattern, &info)) {
		// 系统异常
		ret = 11;
		return ret;
	}

	// 目录
	if (info.type == TB_FILE_TYPE_DIRECTORY) {
		if (path[tb_strlen(pattern) - 1] != '/') {
			tb_strcat(path, "/");
		}
		tb_strcat(path, "*");
		tb_trace_w("%s glob path:[%s] TB_FILE_TYPE_DIRECTORY",
			   __FUNCTION__, path);
	}

	tb_trace_w("%s glob path:[%s]", __FUNCTION__, path);

	ret = glob(path, flags, err_func, &globres);
	if (ret) {
		return ret;
	}

	for (index = 0; index < globres.gl_pathc; index++) {
		if (!tb_file_info(globres.gl_pathv[index], &info)) {
			// 系统异常
			ret = 11;
			return ret;
		}

		if (info.type == TB_FILE_TYPE_DIRECTORY) {
			glob_recursive(globres.gl_pathv[index], flags, list);
		} else if (info.type == TB_FILE_TYPE_FILE) {
			tb_trace_w("%s glob insert path:[%s]", __FUNCTION__,
				   globres.gl_pathv[index]);

			tb_char_t *path = tb_malloc0_cstr(
				tb_strlen(globres.gl_pathv[index]) + 1);
			tb_strcpy(path, globres.gl_pathv[index]);
			tb_list_insert_tail(list, path);
		} else {
			// 未知类型跳过
			tb_trace_w("%s glob path:[%s], info.type:[%d] ?????",
				   __FUNCTION__, globres.gl_pathv[index],
				   info.type);
			continue;
		}
	}
	globfree(&globres);
	return ret;
}

int demo_glob_recursive_main(int argc, char *argv[])
{
	tb_int_t ret = EXIT_SUCCESS;
	if (argc < 2) {
		fprintf(stderr, "<str>");
		exit(EXIT_FAILURE);
	}

	tb_list_ref_t list = tb_list_init(0, tb_element_long());
	ret = glob_recursive(argv[1], GLOB_TILDE, list);

	tb_rfor_all(tb_char_t *, item, list)
	{
		tb_trace_d("item: %s", item);
		tb_free(item);
	}

	tb_list_exit(list);

	return ret;
}
