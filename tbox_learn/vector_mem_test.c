#include <stdlib.h>
#include <tbox/container/iterator.h>
#include <tbox/container/vector.h>
#include <tbox/tbox.h>

#define Num 4

static tb_void_t tb_vector_mem_free(tb_element_ref_t element, tb_pointer_t buff)
{
	tb_trace_i("ifm free: %s, priv: %s", buff, element->priv);
}

static tb_void_t tb_vector_mem_dump(tb_vector_ref_t vector)
{
	tb_trace_i("ifm size: %lu, maxn: %lu", tb_vector_size(vector),
		   tb_vector_maxn(vector));
	tb_for_all(tb_char_t *, item, vector)
	{
		tb_trace_i("ifm at[%lu]: %s", item_itor, item);
	}
}

int demo_vector_mem_main(int argc, char *argv[])
{
	if (!tb_init(tb_null, tb_null)) {
		return -1;
	}

	tb_vector_ref_t vector = tb_null;
	vector = tb_vector_init(0,
				tb_element_mem(110, tb_vector_mem_free, "ifm"));

	tb_assert_and_check_return_val(vector, -1);

	tb_trace_i(
		"=============================================================");
	tb_trace_i("insert:");
	tb_vector_ninsert_head(vector, "HhhhhhhhhhhhhhhhhhHHHHHHHHH", 10);
	tb_vector_ninsert_tail(vector, "TTTTTTTTTT", 10);
	tb_vector_insert_prev(vector, 10, "0000000000");
	tb_vector_insert_prev(vector, 10, "1111111111");
	tb_vector_insert_prev(vector, 10, "2222222222");
	tb_vector_insert_prev(vector, 10, "3333333333");
	tb_vector_insert_prev(vector, 10, "4444444444");
	tb_vector_insert_prev(vector, 10, "5555555555");
	tb_vector_insert_prev(vector, 10, "6666666666");
	tb_vector_insert_prev(vector, 10, "7777777777");
	tb_vector_insert_prev(vector, 10, "8888888888");
	tb_vector_insert_prev(vector, 10, "9999999999");
	tb_vector_insert_head(vector, "4444444444");
	tb_vector_insert_head(vector, "3333333333");
	tb_vector_insert_head(vector, "2222222222");
	tb_vector_insert_head(vector, "1111111111");
	tb_vector_insert_head(vector, "0000000000");
	tb_vector_insert_tail(vector, "5555555555");
	tb_vector_insert_tail(vector, "6666666666");
	tb_vector_insert_tail(vector, "7777777777");
	tb_vector_insert_tail(vector, "8888888888");
	tb_vector_insert_tail(vector, "9999999999");
	tb_vector_mem_dump(vector);

	tb_trace_i(
		"=============================================================");
	tb_trace_i("remove:");
	tb_vector_nremove_head(vector, 5);
	tb_vector_nremove_last(vector, 5);
	tb_vector_mem_dump(vector);

	tb_trace_i(
		"=============================================================");
	tb_trace_i("replace:");
	tb_vector_nreplace_head(vector, "TTTTTTTTTT", 10);
	tb_vector_nreplace_last(vector, "HHHHHHHHHH", 10);
	tb_vector_replace_head(vector, "OOOOOOOOOO");
	tb_vector_replace_last(vector, "OOOOOOOOOO");
	tb_vector_mem_dump(vector);

	tb_trace_i(
		"=============================================================");
	tb_trace_i("clear:");
	tb_vector_clear(vector);
	tb_vector_mem_dump(vector);

	tb_vector_exit(vector);

	tb_exit();
	return 0;
}
