#include <stdio.h>
#include <stdlib.h>
#include <tbox/container/element.h>
#include <tbox/container/heap.h>
#include <tbox/container/queue.h>
#include <tbox/math/random/random.h>
#include <tbox/memory/allocator.h>
#include <tbox/memory/default_allocator.h>
#include <tbox/prefix/malloc.h>
#include <tbox/tbox.h>

int demo_heap_main(int argc, char *argv[])
{
	if (!tb_init(tb_null, tb_null)) {
		return EXIT_FAILURE;
	}
	tb_trace_i("heap min");

	// 初始化
	tb_heap_ref_t heap = tb_heap_init(16, tb_element_uint32());
	tb_assert_and_check_return_val(heap, -1);

	// 重置 rand
	tb_random_reset(tb_true);

	// 生成 heap 数据
	tb_size_t i = 0;
	for (i = 0; i < 100; i++) {
		tb_uint32_t val = (tb_uint32_t)tb_random_range(0, 50);

		// 打印
		tb_trace_i("heap min put:%u", val);

		tb_heap_put(heap, tb_u2p(val));
	}

	// 重置 rand
	tb_random_reset(tb_true);

	for (i = 0; i < 100; i++) {
		tb_uint32_t val = (tb_uint32_t)tb_random_range(0, 50);

		tb_trace_i("heap min rem:%u", val);
		if (!(i & 3)) {
			tb_size_t itor = tb_find_all(heap, &val);
			if (itor != tb_iterator_tail(heap)) {
				tb_heap_remove(heap, itor);
			}
		}
	}

	for (i = 0; i < 39; i++) {
		tb_uint32_t val = (tb_uint32_t)tb_random_range(0, 50);
		tb_trace_i("heap min put:%u", val);
		tb_heap_put(heap, tb_u2p(val));
	}

	tb_trace_i("");

	// dump heap
	while (tb_heap_size(heap)) {
		// put it
		tb_uint32_t val = (tb_uint32_t)(tb_size_t)tb_heap_top(heap);

		// trace
		tb_trace_i("heap_min: pop: %u", val);

		// pop it
		tb_heap_pop(heap);
	}

	// exit heap
	tb_heap_exit(heap);

	tb_exit();
	return EXIT_SUCCESS;
}
