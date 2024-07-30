#define TB_TRACE_MODULE_NAME "list_test"
#define TB_TRACE_MODULE_DEBUG    (1)

#include <stdlib.h>
#include <tbox/tbox.h>

#define Num 4


int demo_list_main(int argc, char *argv[])
{
	if (!tb_init(tb_null, tb_null)) {
		return -1;
	}

	tb_list_ref_t list = tb_null;
	list = tb_list_init(0, tb_element_long());

	tb_assert_and_check_return_val(list, -1);

	int *is = (int *)tb_malloc(sizeof(tb_long_t) * Num);
	tb_assert_and_check_return_val(is, -1);

	for (size_t i = 0; i < Num; i++) {
		is[i] = tb_random_range(0, 100);
	}

	for (size_t i = 0; i < Num; i++) {
		// 先转 tb_long_t * (确保数据大小) 再转 tb_pointer_t
		tb_list_insert_head(list, (tb_pointer_t)(tb_long_t *)&is[i]);
	}

	tb_for_all(tb_long_t const *, item, list)
	{
		// print
		tb_trace_i("item: %d", *item);
	}

	tb_trace_i("list.sizt: %d", tb_list_size(list));

	tb_free(is);
	tb_list_clear(list);
	tb_list_exit(list);

	tb_exit();
	return 0;
}
