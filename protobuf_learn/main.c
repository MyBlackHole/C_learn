#include <stdlib.h>
#include <stdio.h>
#include "test.pb-c.h"
#include "subdir/test2.pb-c.h"

int main(int argc, char **argv)
{
	Test__Test test = TEST__TEST__INIT;
	Test__TestCase comment = TEST__TEST_CASE__INIT;
	comment.name = "test";
	Test__TestCase *comment_ref = &comment;

	printf("%s, %p\n", comment.name, comment.name);

	Test2__TestCase2 comment2 = TEST2__TEST_CASE2__INIT;
	comment2.name = "test2";
	Test2__TestCase2 *comment2_ref = &comment2;

	printf("%s, %p\n", comment2.name, comment2.name);

	test.case_ = &comment_ref;
	test.n_case_ = 1;
	test.case2 = &comment2_ref;
	test.n_case2 = 1;

	printf("size %ld\n", test__test__get_packed_size(&test));
	return EXIT_SUCCESS;
}
