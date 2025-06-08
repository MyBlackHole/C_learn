#include <stdio.h>
#include <stdlib.h>
#include <tbox/algorithm/sort.h>
#include <tbox/container/array_iterator.h>
#include <tbox/container/element.h>
#include <tbox/container/heap.h>
#include <tbox/container/iterator.h>
#include <tbox/prefix/type.h>
#include <tbox/tbox.h>

typedef struct Test {
	long long d;
	long long p;
} Test;

tb_long_t heap_greedy_iterator_comp(tb_element_ref_t element,
				    tb_cpointer_t ldata, tb_cpointer_t rdata)
{
	if (((Test *)ldata)->d == ((Test *)rdata)->d) {
		return 0;
	}
	return ((Test *)ldata)->d > ((Test *)rdata)->d ? 1 : -1;
}

tb_long_t sort_greedy__iterator_comp(tb_iterator_ref_t iterator,
				     tb_cpointer_t litem, tb_cpointer_t ritem)
{
	if (((Test *)litem)->d == ((Test *)ritem)->d) {
		return 0;
	}
	return ((Test *)litem)->d > ((Test *)ritem)->d ? 1 : -1;
}

int main(int argc, char *argv[])
{
	if (!tb_init(tb_null, tb_null)) {
		return EXIT_FAILURE;
	}

	long long n, i, ret;

	// 数据初始化
	ret = scanf("%lld", &n);
	tb_assert_and_check_return_val(ret, -1);

	tb_pointer_t *data = tb_nalloc0(n + 1, sizeof(Test *));
	tb_array_iterator_t ptr_iterator;
	tb_iterator_ref_t iterator =
		tb_array_iterator_init_ptr(&ptr_iterator, data, n);

	for (i = 1; i <= n; i++) {
		Test *item = tb_malloc0(sizeof(Test));
		data[i] = item;
		ret = scanf("%lld%lld", &item->d, &item->p);
	}

	// 排序
	tb_sort(iterator, 1, n + 1, sort_greedy__iterator_comp);

	// // 打印
	// for (i = 1; i <= n; i++)
	// {
	//     tb_trace_i("%lld", ((Test*)data[i])->d);
	// }

	// 堆
	tb_element_t element = tb_element_ptr(tb_null, tb_null);
	element.comp = heap_greedy_iterator_comp;
	tb_heap_ref_t heap = tb_heap_init(16, element);
	tb_assert_and_check_return_val(heap, -1);

	long long ans = 0;
	for (i = 1; i <= n; i++) {
		if (((Test *)data[i])->d <= (long long)tb_heap_size(heap)) {
			if (((Test *)tb_heap_top(heap))->p <
			    ((Test *)data[i])->p) {
				ans += ((Test *)data[i])->p -
				       ((Test *)tb_heap_top(heap))->p;
				tb_heap_pop(heap);
				tb_heap_put(heap, data[i]);
			}
		} else {
			ans += ((Test *)data[i])->p;
			tb_heap_put(heap, data[i]);
		}
	}

	tb_trace_i("ans: %lld ", ans);

	// // heap test
	// for (i = 1; i <= n; i++)
	// {
	//     // put it
	//     Test* val = tb_heap_top(heap);

	//     // trace
	//     tb_trace_i("heap max: pop: %u - %p", val->d, val);

	//     // pop it
	//     tb_heap_pop(heap);
	// }

	// // 释放内存
	for (i = n; i >= 1; i--) {
		tb_free(data[i]);
	}

	tb_free(data);
	tb_heap_exit(heap);

	tb_exit();
	return EXIT_SUCCESS;
}
