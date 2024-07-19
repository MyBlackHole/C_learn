#include <stdio.h>
#include <stdlib.h>
#include <tbox/libc/string/string.h>
#include <tbox/memory/allocator.h>
#include <tbox/memory/default_allocator.h>
#include <tbox/memory/large_allocator.h>
#include <tbox/prefix/malloc.h>
#include <tbox/tbox.h>

int demo_allocator_main(int argc, char *argv[])
{
	if (!tb_init(tb_null, tb_null)) {
		return EXIT_FAILURE;
	}
	tb_trace_i("mem allocator");

	tb_allocator_ref_t allocator = tb_null;
	tb_allocator_ref_t large_allocator = tb_null;

	do {
		large_allocator = tb_large_allocator_init(tb_null, 0);
		tb_assert_and_check_break(large_allocator);

		allocator = tb_default_allocator_init(large_allocator);
		tb_assert_and_check_break(allocator);

		tb_pointer_t data = tb_allocator_malloc(allocator, 10);
		tb_assert_and_check_break(data);

		tb_trace_i("allocator malloc success");
		tb_memset(data, 0, 10 + 1);

		tb_allocator_free(allocator, data);
#ifdef __tb_debug__
		// dump allocator
		tb_allocator_dump(allocator);
#endif
	} while (0);

	if (allocator) {
		tb_allocator_exit(allocator);
		allocator = tb_null;
	}
	tb_exit();
	return EXIT_SUCCESS;
}
