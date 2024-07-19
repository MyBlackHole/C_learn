#include <stdio.h>
#include <stdlib.h>
#include <tbox/container/element.h>
#include <tbox/container/heap.h>
#include <tbox/container/queue.h>
#include <tbox/math/random/random.h>
#include <tbox/tbox.h>

typedef struct Test {
	int a;
	int b;
} Test;

static tb_long_t tb_test_heap_min_comp(tb_element_ref_t element,
				       tb_cpointer_t ldata, tb_cpointer_t rdata)
{
	return ((((Test *)ldata)->a < ((Test *)rdata)->a) ? -1 : 1);
}

int demo_heap1_main(int argc, char *argv[])
{
	if (!tb_init(tb_null, tb_null)) {
		return EXIT_FAILURE;
	}
	tb_trace_i("heap min");

	// 初始化
	tb_element_t element = tb_element_ptr(tb_null, tb_null);
	element.comp = tb_test_heap_min_comp;

	tb_heap_ref_t heap = tb_heap_init(16, element);
	tb_assert_and_check_return_val(heap, EXIT_FAILURE);

	// 重置 rand
	tb_random_reset(tb_true);

	// 生成 heap 数据
	tb_size_t index = 0;
	for (index = 0; index < 10; index++) {
		tb_uint32_t val = (tb_uint32_t)tb_random_range(0, 50);

		Test *test = malloc(sizeof(Test));
		test->a = val;

		// 打印
		tb_trace_i("heap min put:%u", val);

		tb_heap_put(heap, test);
	}

	// dump heap
	while (tb_heap_size(heap)) {
		// put it
		Test *t = tb_heap_top(heap);

		// trace
		tb_trace_i("heap_min: pop: %u", t->a);

		// pop it
		tb_heap_pop(heap);
		free(t);
	}

	// exit heap
	tb_heap_exit(heap);

	tb_exit();
	return EXIT_SUCCESS;
}
