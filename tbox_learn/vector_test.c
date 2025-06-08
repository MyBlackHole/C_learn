#include <stdlib.h>
#include <tbox/container/iterator.h>
#include <tbox/container/vector.h>
#include <tbox/tbox.h>

#define Num 4

int demo_vector_main(int argc, char *argv[])
{
	if (!tb_init(tb_null, tb_null)) {
		return -1;
	}

	tb_vector_ref_t vector = tb_null;
	vector = tb_vector_init(0, tb_element_long());

	tb_assert_and_check_return_val(tb_vector_resize(vector, 30), -1);

	tb_assert_and_check_return_val(vector, -1);

	int *is = (int *)malloc(sizeof(tb_long_t) * Num);
	tb_assert_and_check_return_val(is, -1);

	for (size_t i = 0; i < Num; i++) {
		is[i] = tb_random_range(0, 100);
	}

	for (size_t i = 0; i < Num; i++) {
		// 先转 tb_long_t * (确保数据大小) 再转 tb_pointer_t
		// // 从头部插入
		// tb_vector_insert_head(vector, (tb_pointer_t)(tb_long_t *)&is[i]);
		tb_vector_insert_tail(vector,
				      (tb_pointer_t)(tb_long_t *)&is[i]);

		// // 指定插入指定位置,
		// tb_vector_insert_prev(vector, 2, (tb_pointer_t)(tb_long_t *)&is[i]);

		// 覆盖指定未知数据
		tb_iterator_copy(vector, 2, (tb_pointer_t)(tb_long_t *)&is[i]);
	}

	tb_for_all(tb_long_t const *, item, vector)
	{
		// print
		if (item != NULL) {
			tb_trace_i("item: %d", *item);
		} else {
			tb_trace_i("&item: %p", item);
		}
	}

	tb_trace_i("vector.sizt: %d", tb_vector_size(vector));
	tb_trace_i("vector.maxn: %d", tb_vector_maxn(vector));
	// tb_trace_i("tb_element_long: %d", tb_element_long());

	tb_trace_i("vector[3]: %d", *(int *)tb_iterator_item(vector, 3));

	tb_vector_clear(vector);
	tb_vector_exit(vector);

	tb_exit();
	return 0;
}
