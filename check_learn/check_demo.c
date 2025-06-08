#include <check.h>
#include <stdio.h>
#include <stdlib.h>

int sub(int a, int b)
{
	return a - b;
}

int add(int a, int b)
{
	return a + b;
}

START_TEST(test_sub)
{
	ck_assert_msg(sub(7, 2) == 5, "error, 7 - 2 != 5");
	ck_assert_msg(sub(6, 2) == 3, "error, 6 - 2 != 4");
}
END_TEST

START_TEST(test_add)
{
	ck_assert(add(7, 2) == 9);
	ck_assert(add(7, 5) == 12);
}
END_TEST

Suite *make_add_suite(void)
{
	Suite *s = suite_create("add"); // 建立Suite
	TCase *tc_math = tcase_create("math"); // 建立测试用例集
	suite_add_tcase(s, tc_math); // 将测试用例加到Suite中
	tcase_add_test(tc_math, test_sub); // 测试用例加到测试集中
	tcase_add_test(tc_math, test_add); // 测试用例加到测试集中
	return s;
}

int demo_check_demo_main(int argc, char *argv[])
{
	SRunner *sr;
	sr = srunner_create(make_add_suite()); // 将Suite加入到SRunner
	srunner_run_all(sr, CK_NORMAL);
	int n = srunner_ntests_failed(sr); // 运行所有测试用例
	printf("failed number %d\n", n);
	srunner_free(sr);

	return 0;
}
