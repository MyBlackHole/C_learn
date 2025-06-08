#include <stdio.h>
#include <stdlib.h>
#include <tbox/algorithm/sort.h>
#include <tbox/container/array_iterator.h>
#include <tbox/container/iterator.h>
#include <tbox/libc/stdio/stdio.h>
#include <tbox/libc/string/string.h>
#include <tbox/math/random/random.h>
#include <tbox/platform/time.h>
#include <tbox/prefix/type.h>
#include <tbox/tbox.h>

int demo_sort_main(int argc, char *argv[])
{
	if (!tb_init(tb_null, tb_null)) {
		return EXIT_FAILURE;
	}
	tb_trace_i("sort");

	int num;
	int ret;
	__tb_volatile__ tb_size_t i = 0;
	ret = scanf("%d", &num);
	tb_assert_and_check_return_val(ret, -1);

	// 初始化数据
	tb_char_t **data = (tb_char_t **)tb_nalloc0(num, sizeof(tb_char_t *));
	tb_assert_and_check_return_val(data, -1);

	// 初始化迭代器
	tb_array_iterator_t array_iterator;
	tb_iterator_ref_t iterator =
		tb_array_iterator_init_str(&array_iterator, data, num);

	// 生成
	tb_char_t string[256] = { 0 };
	for (i = 0; i < num; i++) {
		tb_long_t r =
			tb_snprintf(string, 256, "%ld", tb_random_value());
		string[r] = '\0';
		data[i] = tb_strdup(string);
	}

	// 排序
	tb_hong_t time = tb_mclock();
	tb_sort_all(iterator, tb_null);
	time = tb_mclock() - time;

	// time
	tb_trace_i("tb_heap_sort_int_all: %lld ms", time);

	// 打印
	for (i = 0; i < num; i++)
		tb_trace_i("sort %d:%s", i, data[i]);

	// 验证
	for (i = 1; i < num; i++)
		tb_assert_and_check_break(tb_strcmp(data[i - 1], data[i]) <= 0);

	// 释放数据内存
	for (i = 0; i < num; i++)
		tb_free(data[i]);
	tb_free(data);

	tb_exit();
	return EXIT_SUCCESS;
}
